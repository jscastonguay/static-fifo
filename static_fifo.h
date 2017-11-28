
/*
  MIT License

  Copyright (c) 2017 Jean-Sébastien Castonguay

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef STATIC_FIFO_H
#define	STATIC_FIFO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define STATIC_FIFO_DEFINE( FIFOName, ElementType, NumberElements) \
\
typedef struct { \
    ElementType  Buffer[NumberElements]; \
    unsigned int ReadIndex; \
    unsigned int WriteIndex; \
    unsigned int Size; \
    unsigned int NumberStored; \
} FIFOName##_t


#define STATIC_FIFO_CREATE( FIFOName, NumberElements) \
\
FIFOName##_t FIFOName = { \
    .ReadIndex    = 0, \
    .WriteIndex   = 0, \
    .Size         = NumberElements, \
    .NumberStored = 0 \
}


#define STATIC_FIFO_DEFINE_AND_CREATE( FIFOName, ElementType, NumberElements) \
    STATIC_FIFO_DEFINE( FIFOName, ElementType, NumberElements); \
    STATIC_FIFO_CREATE( FIFOName, NumberElements);


#define STATIC_FIFO_EXTERN( FIFOName) extern FIFOName##_t FIFOName

#define STATIC_FIFO_GET_NUMBER_ELEMENTS( FIFOName) ((FIFOName).NumberStored)

#define STATIC_FIFO_IS_FULL( FIFOName) ((FIFOName).NumberStored >= (FIFOName).Size)

#define STATIC_FIFO_IS_EMPTY( FIFOName) ((FIFOName).NumberStored == 0)

#define STATIC_FIFO_PUSH( FIFOName, Element, Result) \
    do { \
        if (STATIC_FIFO_IS_FULL( FIFOName)) { \
            Result = false; \
        } else { \
            (FIFOName).Buffer[(FIFOName).WriteIndex] = Element; \
            (FIFOName).WriteIndex++; \
            (FIFOName).NumberStored++; \
            if ((FIFOName).WriteIndex >= (FIFOName).Size) { \
                (FIFOName).WriteIndex = 0; \
            } \
            Result = true; \
        } \
    } while (false)


#define STATIC_FIFO_POP( FIFOName, Element, Result) \
    do { \
        if (STATIC_FIFO_IS_EMPTY( FIFOName)) { \
            Result = false; \
        } else { \
            Element = FIFOName.Buffer[(FIFOName).ReadIndex]; \
            (FIFOName).ReadIndex++; \
            (FIFOName).NumberStored--; \
            if ((FIFOName).ReadIndex >= (FIFOName).Size) { \
                (FIFOName).ReadIndex = 0; \
            } \
            Result = true; \
        } \
    } while(false)


#define STATIC_FIFO_EMPTY( FIFOName) \
    do { \
        (FIFOName).ReadIndex    = 0; \
        (FIFOName).WriteIndex   = 0; \
        (FIFOName).NumberStored = 0; \
    } while (false)

#ifdef	__cplusplus
}
#endif

#endif