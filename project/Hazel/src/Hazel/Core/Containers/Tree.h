#pragma once

namespace Hazel {

	template<typename T>
	class Tree {
	 private:
		using max_child_t = uint8_t;
		using max_height_t = uint8_t;
		using max_node_t = uint16_t;

		//------------
		//--- Node ---
		//------------

		struct Node {
		 public:
			Node() : m_Data() {}

			~Node() {}

			template<typename ... Args>
			Node(Args&& ... args)
			  : m_Data(args...)
			{}

			template<typename ... Args>
			T& AddChild(Args&& ... args)
			{
				AddChildPtr();
				m_ChildPtrs[m_ChildAmount-1] = new Node(std::forward<Args>(args)...);
				return m_ChildPtrs[m_ChildAmount-1]->GetData();
			}

			void AddChildPtr()
			{
				auto newChilds = new Node*[m_ChildAmount + 1];
				for (size_t i = 0; i < m_ChildAmount; i++)
					newChilds[i] = m_ChildPtrs[i];

				delete [] m_ChildPtrs;
				m_ChildPtrs = newChilds;

				m_ChildAmount++;
			}

			T& GetData()
			{
				return m_Data;
			}

		 public:
			T m_Data;
			max_child_t m_ChildAmount = 0;
			Node** m_ChildPtrs = nullptr;
		};

		//----------------
		//--- Iterator ---
		//----------------

	 public:
		class Iterator {
		 public:
			Iterator(T** dataPtr) 
				: m_Current(dataPtr)
			{}
		
			Iterator& operator++()
			{
				m_Current++;
				return *this;
			}

			T& operator*()
			{
				return **m_Current;
			}

			bool operator==(const Iterator& other) const
			{
				return m_Current == other.m_Current;
			}

			bool operator!=(const Iterator& other) const
			{
				return m_Current != other.m_Current;
			}

		 private:
			T** m_Current;
		};
	
		//---------------
		//--- Reverse ---
		//---------------
	
	 private:
		struct ReversedInterator {
		 public:
			ReversedInterator(T** dataPtr) 
				: m_Current(dataPtr)
			{}
		
			ReversedInterator& operator++()
			{
				m_Current--;
				return *this;
			}

			T& operator*()
			{
				return **m_Current;
			}

			bool operator==(const ReversedInterator& other) const
			{
				return m_Current == other.m_Current;
			}

			bool operator!=(const ReversedInterator& other) const
			{
				return m_Current != other.m_Current;
			}

		 private:
			T** m_Current;
		};

		struct ReversedTree {
			ReversedInterator begin() { 
				if (m_Tree.m_NeedToSort)
					m_Tree.SortList();
				return ReversedInterator(m_Tree.m_List + m_Tree.m_NodeAmount -1);
			}
			ReversedInterator end() { 
				if (m_Tree.m_NeedToSort)
					m_Tree.SortList();
				return ReversedInterator(m_Tree.m_List -1);
			}
			Tree<T> m_Tree;
		};

		//------------
		//--- Tree ---
		//------------

	 public:
		Tree()
		{}
		
		template<typename ... Args>
		Tree(Args&& ... rootArgs)
			: m_Root(std::forward<Args>(rootArgs)...)
		{}
		
		Tree(const Tree<T>& other) = default;
		Tree& operator=(const Tree<T>& other) = default;
	
		template<typename LBD, typename ... Args>
		T* push(const LBD& lambdaCondition, Args&& ... args) 
		{
			return push_further(m_Root, lambdaCondition, std::forward<Args>(args)...);
		}

		Iterator begin() 
		{
			if (m_NeedToSort)
				SortList();
			return Iterator(m_List);
		}

		Iterator end()
		{
			if (m_NeedToSort)
				SortList();
			return Iterator(m_List+m_NodeAmount);
		}

		ReversedTree& reversed()
		{
			return *((ReversedTree*)this);
		}

	 private:
		template<typename LBD, typename ... Args>
		T* push_further(Node& node, const LBD& lambdaCondition, Args&& ... args) 
		{
			T* ptr = nullptr;

			if (node.m_ChildPtrs) 
				for (int i = node.m_ChildAmount -1; i >= 0 && !ptr; i--)
					ptr = push_further(*node.m_ChildPtrs[i], lambdaCondition, std::forward<Args>(args)...);

			if (!ptr)
				if (lambdaCondition(node.GetData())){
					ptr = &(node.AddChild(std::forward<Args>(args)...));
					m_NodeAmount++;
					m_NeedToSort = true;
				}

			return ptr;
		}

		void SortList()
		{
			delete [] m_List;
			m_List = new T*[m_NodeAmount];
		
			m_CurrentNode = 0;
		
			if (m_Root.m_ChildPtrs) 
				for (int i = m_Root.m_ChildAmount -1; i >= 0; i--)
					SortFurther(*m_Root.m_ChildPtrs[i]);

			m_NeedToSort = false;
		}

		void SortFurther (Node& node)
		{
			if (node.m_ChildPtrs) 
				for (int i = node.m_ChildAmount -1; i >= 0; i--)
					SortFurther(*node.m_ChildPtrs[i]);

			m_List[m_CurrentNode] = &node.m_Data;
			m_CurrentNode++;
		}

	 private:
		Node m_Root;
		max_node_t m_NodeAmount = 0;

		bool m_NeedToSort = false;
		T** m_List = nullptr;
		max_node_t m_CurrentNode = 0;
	};

}
