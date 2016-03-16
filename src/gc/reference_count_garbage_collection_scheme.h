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
#ifndef COREVM_REFERENCE_COUNT_GARBAGE_COLLECTION_SCHEME_H_
#define COREVM_REFERENCE_COUNT_GARBAGE_COLLECTION_SCHEME_H_

#include "garbage_collection_scheme.h"

#include "corevm/macros.h"
#include "dyobj/dynamic_object.h"
#include "dyobj/dynamic_object_heap.h"
#include "dyobj/dynamic_object_manager.h"


#include <cstdint>


namespace corevm {


namespace gc {


class reference_count_garbage_collection_scheme : public garbage_collection_scheme
{
public:
  typedef class dynamic_object_manager : public dyobj::dynamic_object_manager
  {
    public:
      dynamic_object_manager();

      virtual inline bool garbage_collectible() const noexcept
      {
        /**
         * An object is only garbage-collectible if it's "attached",
         * meaning that it has been used either as a reference or
         * placed in a frame. This will help make sure that temporary objects
         * sitting on the object stack not being garbage-collected.
         */
        return m_count == 0 && m_attached;
      }

      virtual inline void on_create() noexcept
      {
        // Do nothing here.
      }

      virtual inline void on_setattr() noexcept
      {
        m_attached = true;
        inc_ref_count();
      }

      virtual inline void on_delattr() noexcept
      {
        dec_ref_count();
      }

      // Define at least one virtula method out-of-line.
      virtual void on_delete() noexcept;

      virtual inline void on_exit() noexcept
      {
        dec_ref_count();
      }

      virtual inline void inc_ref_count() noexcept
      {
        ++m_count;
      }

      virtual inline void dec_ref_count() noexcept
      {
        if (m_count > 0)
        {
          --m_count;
        }
      }

      uint64_t ref_count() const
      {
        return m_count;
      }

    protected:
      uint64_t m_count;
      bool m_attached;
  } reference_count_dynamic_object_manager;

  using dynamic_object_type = typename dyobj::dynamic_object<reference_count_dynamic_object_manager>;
  using dynamic_object_heap_type = typename dyobj::dynamic_object_heap<reference_count_dynamic_object_manager>;

  virtual void gc(dynamic_object_heap_type&) const;

#if COREVM_457
  template<typename dynamic_object_heap_type>
  class heap_iterator
  {
    public:
      explicit heap_iterator(
        dynamic_object_heap_type& heap,
        const reference_count_garbage_collection_scheme& scheme)
        :
        m_heap(heap),
        m_scheme(scheme)
      {
      }

      void operator()(
        typename dynamic_object_heap_type::dynamic_object_id_type /* id */,
        typename dynamic_object_heap_type::dynamic_object_type& object)
      {
        m_scheme.check_and_dec_ref_count(m_heap, object);
        m_scheme.resolve_self_reference_cycles(m_heap, object);
      }

    private:
      dynamic_object_heap_type& m_heap;
      const reference_count_garbage_collection_scheme& m_scheme;
  };

  friend class heap_iterator<dynamic_object_heap_type>;

protected:
  void check_and_dec_ref_count(dynamic_object_heap_type&, dynamic_object_type&) const;

  void resolve_self_reference_cycles(dynamic_object_heap_type&, dynamic_object_type&) const;
  void remove_cycles(dynamic_object_heap_type&) const;
#endif /* if COREVM_457 */
};


} /* end namespace gc */


} /* end namespace corevm */


#endif /* COREVM_REFERENCE_COUNT_GARBAGE_COLLECTION_SCHEME_H_ */
