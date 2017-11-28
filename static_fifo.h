
/* Copyright (C) 2013  Jean-Sebastien Castonguay, ing.
 *
 * static_fifo.h is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * static_fifo.h is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with static_fifo.h.  If not, see <http://www.gnu.org/licenses/>. */

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

#endif	/* STATIC_FIFO_H */