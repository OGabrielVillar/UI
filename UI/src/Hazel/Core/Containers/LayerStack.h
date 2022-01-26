#pragma once
#include "pch.h"

namespace Hazel::Containers {

	template<typename T>
	class layerstack {

	private:
		template<typename TL>
		class _layer {
		public:
			_layer(TL* data_in) : data(data_in) {
			}
			_layer(TL* data_in, _layer* lower_layer_in) : data(data_in), lower_layer(lower_layer_in) {
				lower_layer->reassignUpperLayerTo(this);
			}
			_layer(TL* data_in, _layer* lower_layer_in, _layer* upper_layer_in) : data(data_in), lower_layer(lower_layer_in), upper_layer(upper_layer_in) {
				lower_layer->reassignUpperLayerTo(this);
				upper_layer->reassignLowerLayerTo(this);
			}
			~_layer() {
				delete data;
			}
		public:
			void reassignLowerLayerTo(_layer* layer_in) {
				lower_layer = layer_in;
			}
			void reassignUpperLayerTo(_layer* layer_in) {
				upper_layer = layer_in;
			}
			void insert(TL* data_in) {
				lower_layer = new _layer<TL>(data_in, lower_layer, this);
			}
			void insertLayerOnTop(TL* data_in) {
			}
			void insertLayerBeneath(TL* data_in) {
			}
		public:
			TL* data;
			_layer<TL>* lower_layer = nullptr;
			_layer<TL>* upper_layer = nullptr;
		};


		template<typename layerstack>
		class _layerstack_iterator {
		public:
			using ValueType = typename layerstack::ValueType;
			using ReferenceType = ValueType&;
		public:
			_layerstack_iterator(_layer<ValueType>* layer_in)
				: m_layer(layer_in) {}

			_layerstack_iterator& operator++() {
				m_layer = m_layer->upper_layer;
				return *this;
			}
			_layerstack_iterator operator++(int) {
				_layerstack_iterator iterator = *this;
				++(*this);
				return iterator;
			}
			_layerstack_iterator& operator--() {
				m_layer = m_layer->lower_layer;
				return *this;
			}
			_layerstack_iterator operator--(int) {
				_layerstack_iterator iterator = *this;
				--(*this);
				return iterator;
			}
			_layerstack_iterator operator[](int index) {
				return nullptr; //TODO
			}
			//_layerstack_iterator operator->() {
			//	return m_layer->data;
			//}
			ReferenceType operator*() {
				return *(m_layer->data);
			}
			bool operator==(const _layerstack_iterator& other) const {
				return m_layer == other.m_layer;
			}
			bool operator!=(const _layerstack_iterator& other) const {
				return m_layer != other.m_layer;
			}
		private:
			_layer<ValueType>* m_layer;
		};


	public:
		template<typename layerstack>
		class _layerstack_reversed_iterator {
		public:
			using ValueType = typename layerstack::ValueType;
			using ReferenceType = ValueType&;
		public:
			_layerstack_reversed_iterator(_layer<ValueType>* layer_in)
				: m_layer(layer_in) {}

			_layerstack_reversed_iterator& operator++() {
				m_layer = m_layer->lower_layer;
				return *this;
			}
			_layerstack_reversed_iterator operator++(int) {
				_layerstack_reversed_iterator iterator = *this;
				++(*this);
				return iterator;
			}
			_layerstack_reversed_iterator& operator--() {
				m_layer = m_layer->upper_layer;
				return *this;
			}
			_layerstack_reversed_iterator operator--(int) {
				_layerstack_reversed_iterator iterator = *this;
				--(*this);
				return iterator;
			}
			_layerstack_reversed_iterator operator[](int index) {
				return nullptr; //TODO
			}
			//_layerstack_reversed_iterator operator->() {
			//	return m_layer->data;
			//}
			ReferenceType operator*() {
				return *(m_layer->data);
			}
			bool operator==(const _layerstack_reversed_iterator& other) const {
				return m_layer == other.m_layer;
			}
			bool operator!=(const _layerstack_reversed_iterator& other) const {
				return m_layer != other.m_layer;
			}
		private:
			_layer<ValueType>* m_layer;
		};

		template <typename RT>
		struct reversed_layerstack {
			using ValueType = RT;
			using Iterator = _layerstack_reversed_iterator<layerstack<ValueType>>;

			Iterator begin() {
				return Iterator(m_topLayer.lower_layer);
			}
			Iterator end() {
				return Iterator(&m_botLayer);
			}

		private:
			uint32_t  m_size = 0;
			_layer<ValueType> m_botLayer; //Start
			_layer<ValueType> m_topLayer; //End
		};

	public:
		using ValueType = T;
		using Iterator = _layerstack_iterator<layerstack<ValueType>>;

	public:
		layerstack() : m_botLayer(nullptr), m_topLayer(nullptr, &m_botLayer) {
		}
		~layerstack() {
		}

	public:
		layerstack& operator<<(T&& data_in) noexcept {
			insert(new T(data_in));
			return *this;
		}

		void insert(T&& data_in) noexcept {
			insert(new T(data_in));
		}
		bool empty() {
			return !(bool)m_size;
		}

		Iterator begin() {
			return Iterator(m_botLayer.upper_layer);
		}
		Iterator end() {
			return Iterator(&m_topLayer);
		}

	public:
		void insert(T* data_in) {
			m_size++;
			m_topLayer.insert(data_in);
		}

	private:
		uint32_t  m_size = 0;
		_layer<ValueType> m_botLayer; //Start
		_layer<ValueType> m_topLayer; //End
	public:
		reversed_layerstack<ValueType>& reversed = *(reversed_layerstack<ValueType>*)this;
	};

}
