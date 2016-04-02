/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2015 Yanzheng Li

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/
#include "corevm/macros.h"
#include "dyobj/dynamic_object.h"
#include "dyobj/dynamic_object_heap.h"
#include "gc/garbage_collector.h"
#include "gc/reference_count_garbage_collection_scheme.h"

#include <gtest/gtest.h>

#include <list>


#if COREVM_457


template<class GarbageCollectionScheme>
class GarbageCollectionUnitTest : public ::testing::Test
{
protected:
  using _GarbageCollectorType = typename corevm::gc::GarbageCollector<GarbageCollectionScheme>;

  using _ObjectType = typename corevm::dyobj::DynamicObject<
    typename GarbageCollectionScheme::DynamicObjectManager>;

  void do_gc_and_check_results(std::list<corevm::dyobj::dyobj_id> ids)
  {
    _GarbageCollectorType collector(m_heap);
    collector.gc();

    ASSERT_EQ(m_heap.size(), ids.size());

    for (auto itr = ids.begin(); itr != ids.end(); ++itr)
    {
      corevm::dyobj::dyobj_id id = static_cast<corevm::dyobj::dyobj_id>(*itr);

      ASSERT_NO_THROW(
        {
          m_heap.at(id);
        }
      );
    }
  }

  corevm::dyobj::dyobj_id help_create_obj()
  {
    corevm::dyobj::dyobj_id id = m_heap.create_dyobj();
    return id;
  }

  void help_setattr(
    corevm::dyobj::dyobj_id src_id, corevm::dyobj::dyobj_id dst_id)
  {
    auto& src_obj = m_heap.at(src_id);
    auto& dst_obj = m_heap.at(dst_id);
    src_obj.putattr(static_cast<corevm::dyobj::attr_key>(dst_id), dst_id);
    dst_obj.manager().on_setattr();
  }

  void help_set_as_non_garbage_collectible(corevm::dyobj::dyobj_id id)
  {
    auto& obj = m_heap.at(id);
    obj.set_flag(corevm::dyobj::flags::DYOBJ_IS_NOT_GARBAGE_COLLECTIBLE);
  }

  corevm::dyobj::DynamicObjectHeap<
    typename GarbageCollectionScheme::DynamicObjectManager> m_heap;
};

// -----------------------------------------------------------------------------

typedef ::testing::Types<
  corevm::gc::RefCountGarbageCollectionScheme
> GarbageCollectionSchemeTypes;

// -----------------------------------------------------------------------------

TYPED_TEST_CASE(GarbageCollectionUnitTest, GarbageCollectionSchemeTypes);

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestOneObject)
{
  /**
   * Tests GC on the following object graph:
   *
   *  obj
   *
   * will result in 0 objects left on the heap.
   */
  this->help_create_obj();

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestSelfReferencedObject)
{
  /**
   * Tests GC on the following object graph:
   *
   * obj --->
   *  ^     |
   *  |_____|
   *
   * will result in 0 object left on the heap.
   */
  corevm::dyobj::dyobj_id id = this->help_create_obj();

  this->help_setattr(id, id);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestSelfReferenceOnNonGarbageCollectibleObject)
{
  /**
   * Tests GC on the following object graph:
   *
   * obj* -->
   *  ^     |
   *  |_____|
   *
   * will result in 1 object left on the heap.
   */
  corevm::dyobj::dyobj_id id = this->help_create_obj();

  this->help_setattr(id, id);
  this->help_set_as_non_garbage_collectible(id);

  this->do_gc_and_check_results({id});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestLinearChain)
{
  /**
   * Tests GC on the following object graph:
   *
   *  obj1 -> obj2 -> obj3 -> obj4
   *
   * will result in 0 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id4);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestLinearChainWithNonGarbageCollectibleObject)
{
  /**
   * Tests GC on the following object graph:
   *
   *  obj1* -> obj2 -> obj3 -> obj4
   *
   * will result in 4 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id4);

  this->help_set_as_non_garbage_collectible(id1);

  this->do_gc_and_check_results({id1, id2, id3, id4});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestLinearChainWithNonGarbageCollectibleObjects)
{
  /**
   * Tests GC on the following object graph:
   *
   *  obj1 -> obj2* -> obj3* -> obj4
   *
   * will result in 3 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id4);

  this->help_set_as_non_garbage_collectible(id2);
  this->help_set_as_non_garbage_collectible(id3);

  this->do_gc_and_check_results({id2, id3, id4});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestSingleCycle)
{
  /**
   * Tests GC on the following object graph:
   *
   * obj1 -> obj2 -> obj3 ->
   *  ^                    |
   *  |____________________|
   *
   * will result in 0 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id1);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestMultipleObjectsPointToOne)
{
  /**
   * Tests GC on the following object graph
   *
   * obj1 --->\
   *           \
   * obj2 ------> obj4
   *           /
   * obj3 --->/
   *
   * will result in 0 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id4);
  this->help_setattr(id2, id4);
  this->help_setattr(id3, id4);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestOnePointsToMultipleObjects)
{
  /**
   * Tests GC on the following object graph
   *
   *        ----> obj2
   *       /
   *      /
   * obj1 ------> obj3
   *      \
   *       \
   *        ----> obj4
   *
   * will result in 0 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id1, id3);
  this->help_setattr(id1, id4);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestNonGarbageCollectibleObjectPointsToMultipleObjects)
{
  /**
   * Tests GC on the following object graph
   *
   *         ----> obj2
   *        /
   *       /
   * obj1* ------> obj3
   *       \
   *        \
   *         ----> obj4
   *
   * will result in 4 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id1, id3);
  this->help_setattr(id1, id4);

  this->help_set_as_non_garbage_collectible(id1);

  this->do_gc_and_check_results({id1, id2, id3, id4});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestAdjacentCycles)
{
  /**
   * Tests GC on the following object graph
   *
   *        ----> obj2 --->
   *       /               \
   *      /                 \
   * obj1 ------> obj3 -----> obj1
   *      \                 /
   *       \               /
   *        ----> obj4 --->
   *
   * will result in 0 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id1, id3);
  this->help_setattr(id1, id4);

  this->help_setattr(id2, id1);
  this->help_setattr(id3, id1);
  this->help_setattr(id4, id1);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestTwoIsolatedCycles)
{
  /**
   * Tests GC on the following object graph
   *
   * obj1 -> obj2 -> obj3  obj4 -> obj5 -> obj6
   *  ^               |     ^                |
   *  |_______________|     |________________|
   *
   * will result in 0 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();
  corevm::dyobj::dyobj_id id5 = this->help_create_obj();
  corevm::dyobj::dyobj_id id6 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id1);

  this->help_setattr(id4, id5);
  this->help_setattr(id5, id6);
  this->help_setattr(id6, id4);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestNestedCycles)
{
  /*
   * Tests GC on the following object graph
   *
   *          ------>------ obj2 ----->-----
   *         /                               \
   *        /                 --- obj5 -->    \
   *       /                /             \    \
   *      /                /               \    \
   * obj1 -->--- obj3 ----->----- obj6 -----> obj1
   *      \                \               /    /
   *       \                \             /    /
   *        \                 --- obj7 -->    /
   *         \                               /
   *          ------>------ obj4 ----->------
   *
   * will result in 0 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();
  corevm::dyobj::dyobj_id id5 = this->help_create_obj();
  corevm::dyobj::dyobj_id id6 = this->help_create_obj();
  corevm::dyobj::dyobj_id id7 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id1, id3);
  this->help_setattr(id1, id4);

  this->help_setattr(id2, id1);
  this->help_setattr(id4, id1);

  this->help_setattr(id3, id5);
  this->help_setattr(id3, id6);
  this->help_setattr(id3, id7);

  this->help_setattr(id5, id1);
  this->help_setattr(id6, id1);
  this->help_setattr(id7, id1);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestCycleWithInwardStub)
{
  /**
   * Tests GC on the following object graph
   *
   * obj1 -> obj2 -> obj3 <- obj4
   *  ^                |
   *  |________________|
   *
   * will result in 0 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id1);
  this->help_setattr(id4, id3);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestCycleWithOutwardStub)
{
  /**
   * Tests GC on the following object graph
   *
   * obj1 -> obj2 -> obj3 -> obj4
   *  ^                |
   *  |________________|
   *
   * will result in 0 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id1);
  this->help_setattr(id3, id4);

  this->do_gc_and_check_results({});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestCycleWithNonGarbageCollectibleInwardStub)
{
  /**
   * Tests GC on the following object graph
   *
   * obj1 -> obj2 -> obj3 <- obj4*
   *  ^                |
   *  |________________|
   *
   * will result in 4 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id1);
  this->help_setattr(id4, id3);

  this->help_set_as_non_garbage_collectible(id4);

  this->do_gc_and_check_results({id1, id2, id3, id4});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestCycleWithTwoInwardStubs)
{
  /**
   * Tests GC on the following object graph
   *
   * obj5-> obj1 -> obj2 -> obj3 <- obj4*
   *         ^                |
   *         |________________|
   *
   * will result in 4 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();
  corevm::dyobj::dyobj_id id5 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id1);
  this->help_setattr(id4, id3);
  this->help_setattr(id5, id1);

  this->help_set_as_non_garbage_collectible(id4);

  this->do_gc_and_check_results({id1, id2, id3, id4});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestCycleWithNonGarbageCollectibleOutwardStub)
{
  /**
   * Tests GC on the following object graph
   *
   * obj1 -> obj2 -> obj3 -> obj4*
   *  ^                |
   *  |________________|
   *
   * will result in 1 object left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id1);
  this->help_setattr(id3, id4);

  this->help_set_as_non_garbage_collectible(id4);

  this->do_gc_and_check_results({id4});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestCycleWithTwoOutwardStubs)
{
  /**
   * Tests GC on the following object graph
   *
   * obj5 <- obj1 -> obj2 -> obj3 -> obj4*
   *          ^                |
   *          |________________|
   *
   * will result in 1 object left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();
  corevm::dyobj::dyobj_id id4 = this->help_create_obj();
  corevm::dyobj::dyobj_id id5 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id1);
  this->help_setattr(id3, id4);
  this->help_setattr(id1, id5);

  this->help_set_as_non_garbage_collectible(id4);

  this->do_gc_and_check_results({id4});
}

// -----------------------------------------------------------------------------

TYPED_TEST(GarbageCollectionUnitTest, TestSingleCycleWithNonGarbageCollectibleObject)
{
  /**
   * Tests GC on the following object graph:
   *
   * obj1 -> obj2* -> obj3 ->
   *  ^                     |
   *  |_____________________|
   *
   * will result in 3 objects left on the heap.
   */
  corevm::dyobj::dyobj_id id1 = this->help_create_obj();
  corevm::dyobj::dyobj_id id2 = this->help_create_obj();
  corevm::dyobj::dyobj_id id3 = this->help_create_obj();

  this->help_setattr(id1, id2);
  this->help_setattr(id2, id3);
  this->help_setattr(id3, id1);

  this->help_set_as_non_garbage_collectible(id2);

  this->do_gc_and_check_results({id1, id2, id3});
}

// -----------------------------------------------------------------------------

#endif /* #if COREVM_457 */
