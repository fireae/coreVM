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
#ifndef COREVM_ZONE_SEGMENT_H_
#define COREVM_ZONE_SEGMENT_H_

#include <cstdint>
#include <cstring>

namespace corevm {
namespace memory {

/** Forward declaration. */
class Zone;

class Segment {
public:
  explicit Segment(size_t size);

  Zone* zone() const;
  void set_zone(Zone* const zone);

  Segment* next() const;
  void set_next(Segment* const next);

  size_t size() const;
  size_t capacity() const;

  uint8_t* start() const;
  uint8_t* end() const;

  // Clears the contents of the segment (but not the header).
  void clear_contents();

  // Clears the header and makes the segment unusable this way.
  void clear_header();

private:
  // Constant byte value used for zapping dead memory in debug mode.
  static const unsigned char kZapDeadByte = 0xcd;

  // Computes the address of the nth byte in this segment.
  uint8_t* address(size_t n) const;

  Zone* m_zone;
  Segment* m_next;
  size_t m_size;
};

} /* end namespace memory */
} /* end namespace corevm */

#endif /* COREVM_ZONE_SEGMENT_H_ */
