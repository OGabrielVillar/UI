#pragma once

#include "pch.h"
#include "PushMethod.h"
#include "../Debug/Dummy.h"
#include "../Math/MathCommon.h"

namespace Hazel::Containers {
	
	template<typename type>
	class Stack {

		using capacity_type = unsigned short;

		using enum PushMethod;

		using ValueType = type;
		using ReferenceType = ValueType&;
		
 /////////////////////////////////////////////////////////////////////////

	 private: // ---------- [Pointers List] ----------
		struct PtrsList { 

		 public:
			PtrsList() = default;
			~PtrsList() { 
				First();
				while(!IsEmpty()) {
					delete *needle;
					//room++;
					nullptrs_amount++;
					NextObj();
				}
				delete[] m_ptrs; 
			}
			PtrsList(capacity_type capacity)
				: m_ptrs(new type*[capacity](nullptr)), 
				m_capacity(capacity), 
				nullptrs_amount(capacity),
				room(capacity)
			{}
			PtrsList(const PtrsList&) = delete;
			PtrsList& operator=(const PtrsList&) = delete;

		 public:
			 
			void Reserve(capacity_type amount);
			bool IsEmpty() { 
				return (m_capacity == nullptrs_amount); 
			}

			bool Delete() {
				if (*needle != nullptr)  {
					delete *needle;
					room++;
					nullptrs_amount++;
					*needle = nullptr;

					if (IsEmpty()) {
						start_index = 0;
						last_obj_index = 0;

					} else {
						if (needle_index == last_obj_index){
							PreviousObj();
							last_obj_index = needle_index;
						
						} else if (needle_index == start_index)
							ShiftCycleBy(1);
					}

					return true;
				}
				return false;
			}

			template <PushMethod method>
			type& Push(const type& other) {

				type* obj = new type(other);
				Track(obj, method);
				return *obj;

			}

			template <PushMethod method = Over>
			type& Push(type&& other) {

				type* obj = new type(other);
				Track(obj, method);
				return *obj;

			}

			template <PushMethod method, typename ... Args>
			type& Push(Args ... args) {

				type* obj = new type(args...);
				Track(obj, method);
				return *obj;

			}

			PtrsList& begin() { 
				*First(); return *this; 
			}
			PtrsList& end() { 
				*LastObj(); return *this; 
			}

			void Track(type* object, PushMethod method) {

				capacity_type hold_needle_index = needle_index;

				switch (method) {
					case Over:
						if (room == 0) break; //TODO: MakeRoom
						LastObj();
						if (*needle != nullptr)
							Next();
						TrackIn(object);
						last_obj_index = needle_index;
					break;
					case Under:
						if (room == 0) break; //TODO: MakeRoom
							First();
							if (*needle != nullptr)
								Previous();
							TrackIn(object);
					break;
					case OverCurrent:
						//TODO:
					break;
					case UnderCurrent:
						//TODO:
					break;
				}

				At(needle_index);

			}

			void TrackIn(type* object) {
				*needle = object;
				room--;
				nullptrs_amount--;
			}

			void ShiftCycleBy(int shift_amount) {
				if (shift_amount == 0) return;
				if (shift_amount > 0) {
					start_index %= (int)m_capacity;
					last_obj_index %= (int)m_capacity;
					needle_index %= (int)m_capacity;
				} else {
					start_index = Math::PositiveModulo(shift_amount + (int)start_index, (int)m_capacity);
					last_obj_index = Math::PositiveModulo(shift_amount + (int)last_obj_index, (int)m_capacity);
					needle_index = Math::PositiveModulo(shift_amount + (int)needle_index, (int)m_capacity);
				}
			}

		 //Needle Functions
			type** Current() { 
				return needle; 
			}
			type** At(capacity_type index) { 
				if (!m_capacity) return needle;
				needle_index = start_index;
				needle_index += index;
				needle_index %= m_capacity;
				needle = m_ptrs + needle_index; 
				return needle; 
			}
			type** First() { 
				needle = m_ptrs + start_index; 
				needle_index = start_index; 
				return needle; 
			}
			type** Last() { 
				First();
				return Previous(); 
			}
			type** Next() { 
				if (!m_capacity) return needle;
				needle_index++;
				needle_index %= m_capacity;
				needle = m_ptrs + needle_index;
				return needle; 
			}
			type** Previous() { 
				needle_index--;
				needle_index = Math::PositiveModulo(needle_index,m_capacity);
				needle = m_ptrs + needle_index;
				return needle; 
			}
			type** LastObj() { 
				needle = m_ptrs + last_obj_index; 
				needle_index = last_obj_index;  
				return needle; 
			}
			type** NextObj() { 
				do Next();
				while(*needle == nullptr && !IsEmpty());
				return needle; 
			}
			type** PreviousObj() { 
				do Previous();
				while(*needle == nullptr && !IsEmpty());
				return needle; 
			}

		 private: // Members
			// the array of pointers
			type** m_ptrs = nullptr;
			capacity_type m_capacity = 0;
			
			// The Needle is the tool that PtrsList uses to make his actions.
			type** needle = nullptr;

			// indices to keep track
			capacity_type start_index = 0;
			capacity_type last_obj_index = 0;
			capacity_type needle_index = 0;

			// empty spaces
			capacity_type room = 0;
			capacity_type nullptrs_amount = 0;
		};

 /////////////////////////////////////////////////////////////////////////
		
	 private: // ---------- [Iterator] ----------
		 
		class _stack_iterator {
		public:
			_stack_iterator(PtrsList& list)
			  : m_list(list), 
				m_index(list.CurrentIndex()),
				m_name(name),
			{}
			_stack_iterator& operator++() {
				obj = *m_list.NextObj();
				return *this;
			}
			_stack_iterator operator++(int) {
				return _stack_iterator(m_list); //TODO
			}
			_stack_iterator& operator--() {
				obj = *m_list.PreviousObj();
				return *this;
			}
			_stack_iterator operator--(int) {
				return _stack_iterator(m_list); //TODO
			}
			_stack_iterator operator[](int index) {
				return **(m_list.At(index));
			}
			ReferenceType operator*() {
				return **(m_list.Current());
			}
			bool operator==(const _stack_iterator& other) const {
				return needle_holder == other.needle_holder;
			}
			bool operator!=(const _stack_iterator& other) const {
				return needle_holder != other.needle_holder;
			}
			
			bool operator==(const _last_iterator& other) const {
				return needle_holder == other.needle_holder;
			}
			bool operator!=(const _last_iterator& other) const {
				return needle_holder != other.needle_holder;
			}

		private:
			PtrsList& m_list;
			capacity_type m_index;//TODO: Rever o método de interação
		};
		
 /////////////////////////////////////////////////////////////////////////

	 public:// -------------------- [STACK] --------------------
		
		using Iterator = _stack_iterator;
		 
		Stack()
		  : m_list(5)
		{}

		void Reserve(capacity_type amount) {
			m_list.Reserve(amount);
		}
		bool IsEmpty() {
			return m_list.IsEmpty();
		}

		bool DeleteCurrent() { return m_list.Delete(); }

		template <PushMethod method = Over>
		type& Push(const type& other) {
			return m_list.Push<method>(other);
		}
		
		template <PushMethod method = Over>
		type& Push(type&& other) {
			return m_list.Push<method>(other);
		}

		template <PushMethod method = Over, typename ... Args>
		type& Push(Args ... args) {
			return m_list.Push<method>(std::forward<Args>(args) ...);
		}

		Iterator begin() {
			return Iterator(m_list.begin());
		}
		
		Iterator end() {
			return Iterator(m_list.end());
		}

	private:
		PtrsList m_list;

 /////////////////////////////////////////////////////////////////////////
	};
}
