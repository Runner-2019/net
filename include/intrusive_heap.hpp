/*
 * Copyright (c) 2023 Runner-2019
 *
 * Licensed under the Apache License Version 2.0 with LLVM Exceptions
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *   https://llvm.org/LICENSE.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef INTRUSIVE_HEAP_HPP_
#define INTRUSIVE_HEAP_HPP_

namespace net {

// A doubly-linked intrusive list maintained in ascending order of the 'SortKey'
// field of the list items.
template <typename T, T* T::*Next, T* T::*Prev, typename Key, Key T::*SortKey>
class intrusive_heap {
 public:
  // Constructor.
  constexpr intrusive_heap() noexcept : head_(nullptr) {}

  // Destructor.
  constexpr ~intrusive_heap() noexcept = default;

  // Check whether this heap is empty.
  constexpr bool empty() const noexcept { return head_ == nullptr; }

  // Get head items of this heap.
  constexpr T* top() const noexcept { return head_; }

  // Pop head items of this heap.
  constexpr T* pop() noexcept {
    T* item = head_;
    head_ = item->*Next;
    if (head_ != nullptr) {
      head_->*Prev = nullptr;
    }
    return item;
  }

  // Insert new items into this heap. Also adjust the heap order
  constexpr void insert(T* item) noexcept {
    if (head_ == nullptr) {
      head_ = item;
      item->*Next = nullptr;
      item->*Prev = nullptr;
    } else if (item->*SortKey < head_->*SortKey) {
      item->*Next = head_;
      item->*Prev = nullptr;
      head_->*Prev = item;
      head_ = item;
    } else {
      // Simple insertion sort to insert item in the right place in the list
      // to keep the list sorted by 'item->*SortKey'.
      auto* insert_after = head_;
      while (insert_after->*Next != nullptr &&
             insert_after->*Next->*SortKey <= item->*SortKey) {
        insert_after = insert_after->*Next;
      }
      auto* insert_before = insert_after->*Next;

      item->*Prev = insert_after;
      item->*Next = insert_before;
      insert_after->*Next = item;
      if (insert_before != nullptr) {
        insert_before->*Prev = item;
      }
    }
  }

  // Remove an item from this heap.
  constexpr void remove(T* item) noexcept {
    auto* prev = item->*Prev;
    auto* next = item->*Next;
    if (prev != nullptr) {
      prev->*Next = next;
    } else {
      head_ = next;
    }
    if (next != nullptr) {
      next->*Prev = prev;
    }
  }

 private:
  T* head_;
};

}  // namespace net
#endif  // INTRUSIVE_HEAP_HPP_
