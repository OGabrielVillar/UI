#pragma once

#include "../Math/MathCommon.h"

namespace Hazel::Geometry {

	namespace Template
	{

		template <typename T>
		struct AABBRect {
			using vec2Type = glm::vec<2,T>;
			using vec4Type = glm::vec<4,T>;
			constexpr AABBRect() = default;
			constexpr AABBRect(const AABBRect& other) = default;
			template <typename D>
			constexpr AABBRect(const AABBRect<D>& other)
				: a_x((T)other.a_x), a_y((T)other.a_y), b_x((T)other.b_x), b_y((T)other.b_y)
			{}
			constexpr AABBRect(const vec4Type& vector)
				: a_x(vector.x), a_y(vector.y), b_x(vector.z), b_y(vector.w)
			{}
			constexpr AABBRect(T a_x, T a_y, T b_x, T b_y)
				: a_x(a_x), a_y(a_y), b_x(b_x), b_y(b_y)
			{}
			constexpr AABBRect(T b_x, T b_y)
				: a_x((T)0), a_y((T)0), b_x(b_x), b_y(b_y)
			{}
			union {
				T a_x = 0.f;
				T x;
				T left;
			};
			union {
				T a_y = 0.f;
				T y;
				T top;
			};
			union {
				T b_x = 0.f;
				T right;
			};
			union {
				T b_y = 0.f;
				T bottom;
			};
			const vec2Type& center() const { 
				return (b() + a()) / T(2);
			}
			float xCenter() const { 
				return (b_x + a_x) / T(2);
			}
			float yCenter() const { 
				return (b_y + a_y) / T(2);
			}
			const vec2Type& a() const { 
				return *((const vec2Type*)&a_x);
			}
			const vec2Type& b() const { 
				return *((const vec2Type*)&b_x);
			}
			inline T width() const { return b_x - a_x; }
			inline T height() const  { return b_y - a_y; }
			inline vec2Type size() const  { 
				return vec2Type(b_x - a_x, b_y - a_y);
			}
			inline AABBRect& SetWidth(T width) 
			{ 
				b_x = a_x + width; 
				return *this; 
			}
			inline AABBRect& SetHeight(T height) 
			{ 
				b_y = a_y + height; 
				return *this; 
			}
			inline AABBRect& SetSize(vec2Type size) 
			{ 
				b_x = a_x + size.x; 
				b_y = a_y + size.y; 
				return *this; 
			}
			inline AABBRect& SetPosition(vec2Type position) 
			{ 
				vec2Type shift = position - *((vec2Type*)&a_x);
				a_x += shift.x;
				a_y += shift.y;
				b_x += shift.x;
				b_y += shift.y;
				return *this; 
			}

			inline AABBRect operator + (T rh) const { return *((vec4Type*)this) + rh; }
			inline AABBRect operator - (T rh) const { return *((vec4Type*)this) - rh; }
			inline AABBRect operator * (T rh) const { return *((vec4Type*)this) * rh; }
			inline AABBRect operator / (T rh) const { return *((vec4Type*)this) / rh; }

			inline AABBRect& operator += (T rh) { *((vec4Type*)this) += rh; return *this; }
			inline AABBRect& operator -= (T rh) { *((vec4Type*)this) -= rh; return *this; }
			inline AABBRect& operator *= (T rh) { *((vec4Type*)this) *= rh; return *this; }
			inline AABBRect& operator /= (T rh) { *((vec4Type*)this) /= rh; return *this; }

			inline AABBRect operator + (const vec2Type& rh) const { return *((vec4Type*)this) + vec4Type(rh, rh); }
			inline AABBRect operator - (const vec2Type& rh) const { return *((vec4Type*)this) - vec4Type(rh, rh); }

			inline AABBRect& operator += (const vec2Type& rh) { *((vec4Type*)this) += vec4Type(rh, rh); return *this; }
			inline AABBRect& operator -= (const vec2Type& rh) { *((vec4Type*)this) -= vec4Type(rh, rh); return *this; }

		 public:
			inline static AABBRect<T> LTRB(T left, T top, T right, T bottom)
			{ return AABBRect(left, top, right, bottom); }
			inline static AABBRect<T> XYWH(T x, T y, T width, T height)
			{ return AABBRect(x, y, x+width, y+height); }
			inline static AABBRect<T> XYWH(const vec2Type& position, const vec2Type& size)
			{ return AABBRect(position.x, position.y, position.x + size.x, position.y + size.y); }
			inline static AABBRect<T> XXYY(T a_x, T b_x, T a_y, T b_y)
			{ return AABBRect(a_x, a_y, b_x, b_y); }
			inline static AABBRect<T> WH(T width, T height)
			{ return AABBRect((T)0, (T)0, width, height); }
		};

	}

	using Rect = Template::AABBRect<float>;
	using intRect = Template::AABBRect<int>;

}
