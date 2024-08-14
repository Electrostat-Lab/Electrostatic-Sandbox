/**
 * @file DynamicBuffer.h
 * @author pavl_g.
 * @brief Represents a dynamic buffer wrapper.
 * @version 0.1
 * @date 2022-08-24
 *
 * @copyright
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Scrappers Team, The AVR-Sandbox Project, Serial4j API.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef DY_BUFFER

#define DY_BUFFER

#include<stdlib.h>
#include<ErrnoUtils.h>
#include<BufferUtils.h>

class AddressesBuffer {
    public:
            /**
             * @brief Allocates a heap buffer of pointers and clears it to 0.
             */
            AddressesBuffer(): startAddress((void**) calloc(1, sizeof(void**))) {
            }

            /**
             * @brief Destructs the allocated buffer cells, this API uses
             *        the BufferUtils which protects against double free callbacks.
             */
            ~AddressesBuffer() {
               this->deallocateAll();
            }

            /**
             * Represents the pointer that groups buffers in a contiguous format using
             * their memory addresses.
             *
             * @note This pointer represents the memory address to the start-address of the buffer.
             * @note New buffers can be added to the contiguous memory after this pointer by
             *       de-referencing it and adding one to the memory address to move it to a new cell block.
             * <p>
             * e.g:
             * 1) First way of adding a new buffer to this pointer using the deep copy:
             *     buffer[index] = (void*) calloc(1, sizeof(void*));
             *     buffer[index] = item;
             *
             * 2) Second way of adding a new buffer to this pointer (the one used here):
             *     *(buffer += count) = (void*) calloc(1, sizeof(void*));
             *     *buffer = item;
             *     buffer -= count;
             *
             * 3) The superficial copy example:
             *     buffer[index] = item;
             * </p>
             */
            void** startAddress;

            /**
             * Retrieves the pointer to this dynamic buffer.
             *
             * @return a pointer to this array of buffers.
             */
            virtual void** getStartAddress() {
                return startAddress;
            }

            /**
             * Retrieves this structure size.
             *
             * @return an integer representing this struct in bytes.
             */
            virtual size_t getBufferSize() {
                return sizeof(struct AddressesBuffer);
            }

            /**
             * Resets the counter to the start address.
             */
            virtual void resetToStartAddress() {
                this->count = 0;
            }

            /**
             * Gets the memory address to the integer of the items count.
             *
             * @return a pointer referring to the memory address of the integer that represents the item counts.
             */
            virtual int* getAddressesCount();

            /**
             * Adds a new buffer address to this buffer of addresses in a new index.
             *
             * @param address a void* buffer to add.
             */
            virtual void add(void* address);

            /**
             * Adds a new buffer on a particular location in this pointer replacing an old one if exists.
             *
             * @param address the index where the new buffer will be located in this pointer.
             * @param item the buffer to add.
             */
            virtual void add(int index, void* address);

            /**
             * Frees a buffer from the memory at a particular index.
             * @warning this method call is expensive as it removes and revalidates the whole buffer from NULL pointers.
             *
             * @param index the index of the buffer to remove.
             */
            virtual void removeAt(int index);

            /**
             * Frees all the buffers of this pointer from the memory.
             */
            virtual void removeAll();

            virtual void deallocateAt(int index);

            /**
             * Deallocates all the buffers pointed by their memory addresses.
             */
            virtual void deallocateAll();

            /**
             * Retrieves a buffer index.
             *
             * @param item the buffer to get its index.
             * @return the buffer index in an integer format.
             */
            virtual int indexOf(void* address);

            /**
             * Retrieves a buffer from this pointer using its index.
             *
             * @param index the index where the buffer is located in this pointer.
             * @return the buffer corresponding to this index.
             */
            virtual void* getAddress(int index);

    private:
        int count = 0;
};

#endif