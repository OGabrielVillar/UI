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

	 private: // ---------- [Needle] ----------
		struct Needle {
			// the needle is the tool that PtrsList uses to make his actions.

			Needle(type**& list_start, const capacity_type& capacity, const capacity_type& obj_amount, const capacity_type& last_obj)
			  : m_needle(list_start),
				r_list_start(list_start),
				m_index(0),
				r_capacity(capacity),
				r_last_obj(last_obj),
				r_obj_amount(obj_amount)
			{}
			Needle(const Needle& other)
			  : m_needle(other.r_list_start),
				r_list_start(other.r_list_start),
				m_index(0),
				r_capacity(other.r_capacity),
				r_last_obj(other.r_last_obj),
				r_obj_amount(other.r_obj_amount)
			{}
			capacity_type Index() const { return m_index; } 
			type** operator()(){ return m_needle; }
			type** Current() const { 
				return m_needle; 
			}
			type** Start() { 
				m_needle = r_list_start; 
				m_index = 0; 
				return m_needle; 
			}
			type** End() { 
				Start();
				return Previous(); 
			}
			type** At(capacity_type index) { 
				if (!r_capacity) return m_needle; // avoiding modulo by 0
				m_index = index;
				m_index %= r_capacity;
				m_needle = r_list_start + m_index;
				return m_needle; 
			}
			type** Next() { 
				if (!r_capacity) return m_needle; // avoiding modulo by 0
				m_index++;
				m_index %= r_capacity;
				m_needle = r_list_start + m_index;
				return m_needle; 
			}
			type** Previous() { 
				m_index--;
				m_index = Math::PositiveModulo(m_index,r_capacity);
				m_needle = r_list_start + m_index;
				return m_needle; 
			}
			type** LastObj() { 
				m_index = r_last_obj; 
				m_needle = r_list_start + m_index;
				return m_needle;  
			}
			type** NextObj() { 
				do Next();
				while(*m_needle == nullptr && r_obj_amount);
				return m_needle; 
			}
			type** PreviousObj() { 
				do Previous();
				while(*m_needle == nullptr && r_obj_amount);
				return m_needle; 
			}

			// my own
			type** m_needle = nullptr;
			capacity_type m_index = 0;
			// references
			type**& r_list_start = nullptr;
			const capacity_type& r_last_obj;
			const capacity_type& r_capacity;
			const capacity_type& r_obj_amount;
		};

 /////////////////////////////////////////////////////////////////////////

	 private: // ---------- [Pointers List] ----------
		class PtrsList { 

		 public:
			PtrsList() = default;
			~PtrsList() { 
				needle.Start();
				while(!IsEmpty()) {
					delete *needle();
					obj_amount--;
					needle.NextObj();
				}
				delete[] m_list_start; 
			}
			PtrsList(capacity_type capacity)
			  : m_list_start(new type*[capacity](nullptr)), 
				m_list_holder(new type*[capacity](nullptr)), 
				m_capacity(capacity),
				room(capacity),
				needle(m_list_start, m_capacity, obj_amount, last_obj_index)
			{}
			PtrsList(const PtrsList&) = delete;
			PtrsList& operator=(const PtrsList&) = delete;

		 public:
			 
			void Reserve(capacity_type amount);
			bool IsEmpty() { 
				return (obj_amount == 0); 
			}
			
			void ClearNullptrs() 
			{
			 //Start index will be zero.
				start_index = 0;
			 //All nullptrs will be dealocated to the end(room).
				room = m_capacity - obj_amount;

			 //If there is no object, return.
				if (IsEmpty()) {
					last_obj_index = 0;
					return;
				}

			 //Calculate last_obj_index.
				last_obj_index = obj_amount - 1;

			 //Transfer all the objects pointers to the holder, setting needle to nullptr in the process.
				needle.Start();
				type** holder = m_list_holder;
				do {
					if (*needle() != nullptr) {
						*holder = *needle();
						*needle() = nullptr;
						holder++;
					}
					needle.Next();
				} while ( needle.Index() != start_index );

			 //Swap m_list_holder and m_list_start.
				type** h = m_list_start;
				m_list_start = m_list_holder;
				m_list_holder = h;

				need_cleaning = false;
			}

			bool Delete() {
				if (*needle() != nullptr)  {
					delete *needle();
					*needle() = nullptr;
					obj_amount--;

					if (IsEmpty()) {
						start_index = 0;
						last_obj_index = 0;
					}
					need_cleaning = true;
					return true;
				}
				return false;
			}

			bool Delete(capacity_type index) {
				needle.At(index);
				return Delete();
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

			void Track(type* object, PushMethod method) {

				switch (method) {
					case Over:
						if (room == 0) break; //TODO: MakeRoom
						needle.LastObj();
						if (*needle() != nullptr)
							needle.Next();
						TrackIn(object);
						room--;
						last_obj_index = needle.Index();
					break;
					case Under:
						if (room == 0) break; //TODO: MakeRoom
							needle.Start();
							if (*needle() != nullptr)
								needle.Previous();
							TrackIn(object);
					break;
					case OverCurrent:
						//TODO:
					break;
					case UnderCurrent:
						//TODO:
					break;
				}

			}

			void TrackIn(type* object) {
				*needle() = object;
				obj_amount++;
			}

			//void ShiftCycleBy(int shift_amount) {
			//	if (shift_amount == 0) return;
			//	if (shift_amount > 0) {
			//		start_index %= (int)m_capacity;
			//		last_obj_index %= (int)m_capacity;
			//		//needle_index %= (int)m_capacity;
			//	} else {
			//		start_index = Math::PositiveModulo(shift_amount + (int)start_index, (int)m_capacity);
			//		last_obj_index = Math::PositiveModulo(shift_amount + (int)last_obj_index, (int)m_capacity);
			//		//needle_index = Math::PositiveModulo(shift_amount + (int)needle_index, (int)m_capacity);
			//	}
			//}
			
		 //Iterator Functions
			
			const Needle& AttachIterator() {
				active_iterators++;
				return needle;
			}
			void DetachIterator() {
				active_iterators--;
				if (active_iterators == 0 && need_cleaning)
					ClearNullptrs();

			}

		 private: // PtrsList Members
			// the array of pointers
			type** m_list_start = nullptr;
			type** m_list_holder = nullptr;
			capacity_type m_capacity = 0;

			// indices to keep track
			capacity_type start_index = 0;
			capacity_type last_obj_index = 0;

			// empty spaces
			capacity_type room = 0;
			capacity_type obj_amount = 0;
			bool need_cleaning = false;

			Needle needle;
			
			// iterators amount
			uint16_t active_iterators = 0;
		};

 /////////////////////////////////////////////////////////////////////////

	 public: // ---------- [Stack Interface] ----------
		struct Interface {
		 public:
			Interface(PtrsList& list, capacity_type index, type* obj)
			  : m_obj(obj),
				m_index(index),
				m_list(list)
			{}
			operator type&(){
				return *m_obj;
			}
			type* operator->() const {
				return m_obj;
			}
			type& operator*() const {
				return *m_obj;
			}
			void Delete(){
				m_list.Delete(m_index);
			}
		 private:
			type* m_obj = nullptr;
			capacity_type m_index = 0;
			PtrsList& m_list;
		};

 /////////////////////////////////////////////////////////////////////////
		
	 private: // ---------- [Iterator] ----------

		class _stack_iterator {
		public:
			_stack_iterator(PtrsList& list)
			  : m_list(list),
				needle(m_list.AttachIterator())
			{}
			~_stack_iterator()	
			{
				m_list.DetachIterator();
			}
			_stack_iterator& operator++() {
				if (needle.r_obj_amount == 0) return *this;
				do {
					m_progress++;
					needle.Next();
				} while(*needle() == nullptr);
				return *this;
			}
			Interface operator*() {
				return Interface(m_list, needle.Index(), *needle());
			}
			bool operator!=(bool) const {
				return (m_progress < needle.r_capacity && *(needle.Current()) != nullptr);
			}

		private:
			PtrsList& m_list;
			Needle needle;
			capacity_type m_progress = 0;
		};
		
 /////////////////////////////////////////////////////////////////////////

	 public:// -------------------- [STACK] --------------------
		
		using Iterator = _stack_iterator;
		 
		Stack()
		  : m_list(50)
		{}

		void Reserve(capacity_type amount) {
			m_list.Reserve(amount);
		}
		bool IsEmpty() {
			return m_list.IsEmpty();
		}

		//bool DeleteCurrent() { return m_list.Delete(); }

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

		// To iterate thru objects
		Iterator begin() { return Iterator(m_list);	}
		bool end() { return true; }

	private:
		PtrsList m_list;

 /////////////////////////////////////////////////////////////////////////
	};
}
