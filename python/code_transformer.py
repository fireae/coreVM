# The MIT License (MIT)

# Copyright (c) 2015 Yanzheng Li

# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

import ast
import optparse
import sys
import traceback


class CodeTransformer(ast.NodeVisitor):

    def __init__(self, options):
        self.options = options
        self.indent_level = 0

    def __indent(self):
        self.indent_level += 1

    def __dedent(self):
        self.indent_level -= 1

    def __indentation(self):
        INDENT = '  '
        return ''.join([INDENT for _ in xrange(self.indent_level)])

    def transform(self):
        with open(self.options.input_file, 'r') as fd:
            tree = ast.parse(fd.read())

        transformed_str = self.visit(tree)

        if self.options.debug_mode:
            print 'Writing the following to %s' % self.options.output_file
            print transformed_str

        with open(self.options.output_file, 'w') as fd:
            fd.write(transformed_str)

    """ ------------------------------ mod --------------------------------- """

    def visit_Module(self, node):
        return '\n'.join([self.visit(stmt) for stmt in node.body])

    """ ----------------------------- stmt --------------------------------- """

    def visit_FunctionDef(self, node):
        base_str = '{indentation}def {func_name}({arguments}):\n'

        base_str = base_str.format(
            indentation=self.__indentation(),
            func_name=node.name,
            arguments=self.visit(node.args),
        )

        self.__indent()

        if node.args.vararg:
            base_str += '{vararg} = __call(list, {vararg})\n'.format(vararg=node.args.vararg)

        base_str += '\n'.join([self.visit(stmt) for stmt in node.body])
        base_str += '\n'

        self.__dedent()

        return base_str

    def visit_ClassDef(self, node):
        base_str = '{indentation}class {class_name}:\n'

        base_str = base_str.format(
            indentation=self.__indentation(),
            class_name=node.name,
            body=''.join([self.visit(stmt) for stmt in node.body])
        )

        self.__indent()

        base_str += ''.join([self.visit(stmt) for stmt in node.body])

        self.__dedent()

        return base_str

    def visit_Return(self, node):
        base_str = '{indentation}return'.format(indentation=self.__indentation())

        if node.value:
            base_str += (' ' + self.visit(node.value))

        base_str += '\n'

        return base_str

    def visit_Assign(self, node):
        base_str = '{indentation}{targets} = {value}\n'.format(
            indentation=self.__indentation(),
            targets=', '.join([self.visit(target) for target in node.targets]),
            value=self.visit(node.value)
        )

        return base_str

    def visit_AugAssign(self, node):
        base_str = '{indentation}{target} = __call({target}.{func}, {value})\n'.format(
            indentation=self.__indentation(),
            target=self.visit(node.target),
            func=self.visit(node.op),
            value=self.visit(node.value)
        )

        return base_str

    def visit_Print(self, node):
        base_str = '{indentation}print'.format(indentation=self.__indentation())

        if node.values:
            base_str += (' ' + '__call(' + self.visit(node.values[0]) + '.__str__' + ')')

        base_str += '\n'

        return base_str

    def visit_For(self, node):
        base_str = '{indentation}for {target} in {iter}:\n'.format(
            indentation=self.__indentation(),
            target=self.visit(node.target),
            iter=self.visit(node.iter)
        )

        self.__indent()

        for stmt in node.body:
            base_str += (self.visit(stmt) + '\n')

        self.__dedent()

        return base_str

    def visit_While(self, node):
        base_str = '{indentation}while {test}:\n'.format(
            indentation=self.__indentation(),
            test=self.visit(node.test)
        )

        self.__indent()

        for stmt in node.body:
            base_str += (self.visit(stmt) + '\n')

        self.__dedent()

        return base_str

    def visit_If(self, node):
        base_str = '{indentation}if {expr}:\n'.format(
            indentation=self.__indentation(),
            expr=self.visit(node.test)
        )

        self.__indent()

        for stmt in node.body:
            base_str += (self.visit(stmt) + '\n')

        self.__dedent()

        if node.orelse:
            base_str += 'else:\n'
            self.__indent()
            for stmt in node.orelse:
                base_str += (self.visit(stmt) + '\n')
            self.__dedent()

        return base_str

    def visit_Expr(self, node):
        return self.visit(node.value)

    def visit_Pass(self, node):
        return '{indentation}pass'.format(indentation=self.__indentation())

    def visit_Break(self, node):
        return '{indentation}break'.format(indentation=self.__indentation())

    def visit_Continue(self, node):
        return '{indentation}continue'.format(indentation=self.__indentation())

    """ ----------------------------- expr --------------------------------- """

    def visit_BoolOp(self, node):
        return (' %s ' % self.visit(node.op)).join(
            [self.visit(value) for value in node.values])

    def visit_BinOp(self, node):
        base_str = '__call({lhs}.{func}, {rhs})'

        return base_str.format(
            lhs=self.visit(node.left),
            func=self.visit(node.op),
            rhs=self.visit(node.right)
        )

    def visit_Lambda(self, node):
        return 'lambda {args}: {body}'.format(
            args=self.visit(node.args),
            body=self.visit(node.body))

    def visit_ListComp(self, node):
        pass

    def visit_Compare(self, node):
        # Note: Only supports one comparison now.
        op = node.ops[0]

        if any(
            (
                isinstance(op, ast.Eq),
                isinstance(op, ast.NotEq),
                isinstance(op, ast.Lt),
                isinstance(op, ast.LtE),
                isinstance(op, ast.Gt),
                isinstance(op, ast.GtE),
            )
        ):
            base_str='{indentation}__call({left}.{op_func}, {right})'.format(
                indentation=self.__indentation(),
                left=self.visit(node.left),
                op_func=self.visit(op),
                right=self.visit(node.comparators[0])
            )
        else:
            # TODO: special support for `is` and `is not` can be removed once
            # dynamic dispatching is supported.
            base_str = '{indentation}{left} {op} {comparator}'.format(
              indentation=self.__indentation(),
              left=self.visit(node.left),
              op=self.visit(op),
              comparator=self.visit(node.comparators[0])
            )

        return base_str

    def visit_Call(self, node):
        base_str = '{indentation}__call({caller}'

        base_str = base_str.format(
            indentation=self.__indentation(),
            caller=self.visit(node.func)
        )

        if node.args:
            base_str += (', ' + ', '.join([self.visit(arg) for arg in node.args]))

        if node.kwargs:
            kwargs_str = ', '.join(
                [
                    '{keyword}={value}'.format(
                        keyword=keyword.arg,
                        value=self.visit(keyword.value)
                    )
                    for keyword in node.keywords
                ]
            )
            base_str += (', ' + kwargs_str)

        if node.starargs:
            base_str += (', ' + '*' + self.visit(node.starargs))

        if node.kwargs:
            base_str += (', ' + '**' + self.visit(node.kwargs))

        base_str += ')'

        base_str = base_str.replace(', )', ')')

        return base_str

    def visit_Num(self, node):
        num_type = 'float' if isinstance(node.n, float) else 'int'
        return '__call({num_type}, {n})'.format(
            num_type=num_type, n=str(node.n))

    def visit_Attribute(self, node):
        return '{expr}.{attr}'.format(
            expr=self.visit(node.value),
            attr=str(node.attr)
        )

    def visit_List(self, node):
        return '__call(list, [' + ', '.join([self.visit(expr) for expr in node.elts]) + '])'

    def visit_Name(self, node):
        return node.id

    def visit_Str(self, node):
        return '__call(str, \"%s\")' % str(node.s)

    """ ---------------------------- boolop -------------------------------- """

    def visit_And(self, node):
        return 'and'

    def visit_Or(self, node):
        return 'or'

    """ --------------------------- operator ------------------------------- """

    def visit_Add(self, node):
        return '__add__'

    def visit_Sub(self, node):
        return '__sub__'

    def visit_Mult(self, node):
        return '__mul__'

    def visit_Div(self, node):
        return '__div__'

    def visit_Mod(self, node):
        return '__mod__'

    """ ---------------------------- unaryop ------------------------------- """

    def visit_Not(self, node):
        return 'not'

    """ ----------------------------- cmpop -------------------------------- """

    def visit_Is(self, node):
        # TODO: special support for `is` and `is not` can be removed once
        # dynamic dispatching is supported.
        return 'is'

    def visit_IsNot(self, node):
        # TODO: special support for `is` and `is not` can be removed once
        # dynamic dispatching is supported.
        print 'is not'

    def visit_Eq(self, node):
        return '__eq__'

    def visit_NotEq(self, node):
        return '__neq__'

    def visit_Lt(self, node):
        return '__lt__'

    def visit_LtE(self, node):
        return '__lte__'

    def visit_Gt(self, node):
        return '__gt__'

    def visit_GtE(self, node):
        return '__gte__'

    """ ------------------------- comprehension ---------------------------- """

    def visit_comprehension(self, node):
        raise NotImplementedError

    """ --------------------------- arguments ------------------------------ """

    def visit_arguments(self, node):
        # A mapping of the closest arguments to their default values by their
        # column offset, for explicit kwargs.
        closest_args_to_defaults = {}

        # Traverse through the default values, and find the closest arguments
        # for each of them, and put them into the mapping above.
        for default in node.defaults:
            closest_arg = None
            for arg in node.args:
                if closest_arg is None:
                    closest_arg = arg
                elif arg.col_offset > closest_arg.col_offset and arg.col_offset < default.col_offset:
                    closest_arg = arg

            assert closest_arg

            closest_args_to_defaults[closest_arg.col_offset] = default

        parts = []

        # Iterate through the arguments.
        for arg in node.args:
            default = closest_args_to_defaults.get(arg.col_offset)
            if default:
                parts.append(arg.id + '=' + self.visit(default))
            else:
                parts.append(arg.id)

        if node.vararg:
            parts.append('*' + node.vararg)

        if node.kwarg:
            parts.append('**' + node.kwarg)

        return ', '.join(parts)


def main():
    parser = optparse.OptionParser(
        usage='usage: %prog [options]',
        version='%prog v0.1')

    parser.add_option(
        '-i',
        '--input',
        action='store',
        dest='input_file',
        help='Input file'
    )

    parser.add_option(
        '-o',
        '--output',
        action='store',
        dest='output_file',
        help='Output file'
    )

    parser.add_option(
        '-d',
        '--debug',
        action='store_true',
        dest='debug_mode',
        help='Debug mode'
    )

    options, _ = parser.parse_args()

    if not options.input_file:
        sys.stderr.write('Input file not specified\n')
        return -1

    if not options.output_file:
        sys.stderr.write('Output file not specified\n')
        return -1

    try:
        transformer = CodeTransformer(options)
        transformer.transform()
    except Exception as ex:
        sys.stderr.write('Failed to process %s\n' % options.input_file)
        sys.stderr.write(str(ex))
        sys.stderr.write('\n')
        if options.debug_mode:
            print traceback.format_exc()
        sys.exit(-1)


if __name__ == '__main__':
    main()
