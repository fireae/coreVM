/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2017 Yanzheng Li

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
#include "segment.h"

namespace corevm {
namespace memory {

// -----------------------------------------------------------------------------

Segment::Segment(size_t size) : m_size(size)
{
}

// -----------------------------------------------------------------------------

Zone*
Segment::zone() const
{
  return m_zone;
}

// -----------------------------------------------------------------------------

void
Segment::set_zone(Zone* const zone)
{
  m_zone = zone;
}

// -----------------------------------------------------------------------------

Segment*
Segment::next() const
{
  return m_next;
}

// -----------------------------------------------------------------------------

void
Segment::set_next(Segment* const next)
{
  m_next = next;
}

// -----------------------------------------------------------------------------

size_t
Segment::size() const
{
  return m_size;
}

// -----------------------------------------------------------------------------

size_t
Segment::capacity() const
{
  return m_size - sizeof(Segment);
}

// -----------------------------------------------------------------------------

uint8_t*
Segment::start() const
{
  return address(sizeof(Segment));
}

// -----------------------------------------------------------------------------

uint8_t*
Segment::end() const
{
  return address(m_size);
}

// -----------------------------------------------------------------------------

void
Segment::clear_contents()
{
  memset(start(), kZapDeadByte, capacity());
}

// -----------------------------------------------------------------------------

void
Segment::clear_header()
{
  memset(this, kZapDeadByte, sizeof(Segment));
}

// -----------------------------------------------------------------------------

uint8_t*
Segment::address(size_t n) const
{
  return reinterpret_cast<uint8_t*>(const_cast<Segment*>(this)) + n;
}

// -----------------------------------------------------------------------------

} /* end namespace memory */
} /* end namespace corevm */
