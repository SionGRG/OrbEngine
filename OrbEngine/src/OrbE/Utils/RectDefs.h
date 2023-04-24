#pragma once

#include <tuple>

#include "OrbE/Utils/BasicMaths.h"

namespace ORB {

	template<typename T=float>
	struct RECT_v2
	{
		union
		{
			struct
			{
				T x, y;
			};
			struct
			{
				T w, h;
			};
		};
	};

	template<typename T=float>
	struct RECT
	{
		union
		{
			struct
			{
				T x, y, w, h;
			};
			struct
			{
				T x, y, width, height;
			};
			struct
			{
				T left, top, right, bottom;
			};
			struct
			{
				RECT_v2<T> position, size;
			};
			struct
			{
				RECT_v2<T> coords, size;
			};
		};

		RECT()
			:x(0), y(0), w(0), h(0)
		{}

		RECT(T _x, T _y, T _w, T _h)
			:x(_x), y(_y), w(_w), h(_h)
		{}

		RECT(RECT_v2<T> position, RECT_v2<T> size)
			:x(position.x), y(position.y), w(size.w), h(size.h)
		{}

	};

	typedef RECT<float> RECTF;


}