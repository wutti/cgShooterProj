#pragma once
//###################################################################
// C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// C++ STL
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>
// windows
#if !defined(__GNUC__)&&(defined(_WIN32)||defined(_WIN64))
	#include <windows.h>
	#include <wchar.h>
#endif
// user types
typedef unsigned int	uint;
typedef unsigned char	uchar;
typedef unsigned short	ushort;
//###################################################################

template <class T> struct tvec2
{
	union{ struct { T r, g; }; struct { T x, y; }; };

	// constructor/set
	tvec2(){ x=y=0; }
	tvec2( T a ){ x=y=a; }						inline void set( T a ){ x=y=a; }
	tvec2( T a, T b ){ x=a;y=b; }				inline void set( T a, T b ){ x=a;y=b; }
	tvec2( const tvec2& v ){ x=v.x;y=v.y; }		inline void set( const tvec2& v ){ x=v.x;y=v.y; }
	tvec2( const T* a ){ x=a[0];y=a[1]; }		inline void set( const T* a ){ x=a[0];y=a[1]; }

	// assignment
	inline tvec2& operator=( T a ){ set(a); return *this; }
	inline tvec2& operator+=( const tvec2& v ){ x+=v.x; y+=v.y; return *this; }
	inline tvec2& operator-=( const tvec2& v ){ x-=v.x; y-=v.y; return *this; }
	inline tvec2& operator*=( const tvec2& v ){ x*=v.x; y*=v.y; return *this; }
	inline tvec2& operator/=( const tvec2& v ){ x/=v.x; y/=v.y; return *this; }
	inline tvec2& operator+=( T a ){ x+=a; y+=a; return *this; }
	inline tvec2& operator-=( T a ){ x-=a; y-=a; return *this; }
	inline tvec2& operator*=( T a ){ x*=a; y*=a; return *this; }
	inline tvec2& operator/=( T a ){ x/=a; y/=a; return *this; }

	// casting
	inline operator T*(){ return &x; }
	inline operator const T*() const { return &x; }

	// array operator
	inline T& operator[]( int i ){ return (&r)[i]; }
	inline const T& operator[]( int i ) const { return (&r)[i]; }
	inline T& at( int i ){ return (&r)[i]; }
	inline const T& at( int i ) const { return (&r)[i]; }

	// unary operators
	inline tvec2 operator+(){ return tvec2(r, g); }
	inline tvec2 operator+() const { return tvec2(r, g); }
	inline tvec2 operator-(){ return tvec2(-r, -g); }
	inline tvec2 operator-() const { return tvec2(-r, -g); }

	// binary operators
	inline tvec2 operator+( const tvec2& v ) const { return tvec2(r+v.r, g+v.g); }
	inline tvec2 operator-( const tvec2& v ) const { return tvec2(r-v.r, g-v.g); }
	inline tvec2 operator*( const tvec2& v ) const { return tvec2(r*v.r, g*v.g); }
	inline tvec2 operator/( const tvec2& v ) const { return tvec2(r/v.r, g/v.g);  }
	inline tvec2 operator+( T a ) const { return tvec2(r+a, g+a); }
	inline tvec2 operator-( T a ) const { return tvec2(r-a, g-a); }
	inline tvec2 operator*( T a ) const { return tvec2(r*a, g*a); }
	inline tvec2 operator/( T a ) const { return tvec2(r/a, g/a); }

	// length, normalize, dot product
	inline T length(){ return (T)(sqrt(r*r+g*g)); }
	inline T length2(){ return (T)(r*r+g*g); }
	inline T dot( const tvec2& v ) const { return (T)(r*v.r+g*v.g); }
	inline tvec2 normalize(){ return tvec2(r, g)/length(); }
};

template <class T> struct tvec3
{
	union { struct { T r, g, b; }; struct { T x, y, z; }; };

	// constructor/set
	tvec3(){ x=y=z=0; }
	tvec3( T a ){ x=y=z=a; }								inline void set( T a ){ x=y=z=a; }
	tvec3( T a, T b, T c ){ x=a;y=b;z=c; }					inline void set( T a, T b, T c ){ x=a;y=b;z=c; }
	tvec3( const tvec3& v ){ x=v.x;y=v.y;z=v.z; }			inline void set( const tvec3& v ){ x=v.x;y=v.y;z=v.z; }
	tvec3( const T* a ){ x=a[0];y=a[1];z=a[2]; }			inline void set( const T* a ){ x=a[0];y=a[1];z=a[2]; }
	tvec3( const tvec2<T>& v, T c ){ x=v.x;y=v.y;z=c; }		inline void set( const tvec2<T>& v, T c ){ x=v.x;y=v.y;z=c; }
	tvec3( T a, const tvec2<T>& v ){ x=a;y=v.x;z=v.y; }		inline void set( T a, const tvec2<T>& v ){ x=a;y=v.x;z=v.y; }

	// assignment
	inline tvec3& operator=( T a ){ set(a); return *this; }
	inline tvec3& operator=( const T* a ){ set(a); return *this; }
	inline tvec3& operator+=( const tvec3& v ){ x+=v.x; y+=v.y; z+=v.z; return *this; }
	inline tvec3& operator-=( const tvec3& v ){ x-=v.x; y-=v.y; z-=v.z; return *this; }
	inline tvec3& operator*=( const tvec3& v ){ x*=v.x; y*=v.y; z*=v.z; return *this; }
	inline tvec3& operator/=( const tvec3& v ){ x/=v.x; y/=v.y; z/=v.z; return *this; }
	inline tvec3& operator+=( T a ){ x+=a; y+=a; z+=a; return *this; }
	inline tvec3& operator-=( T a ){ x-=a; y-=a; z-=a; return *this; }
	inline tvec3& operator*=( T a ){ x*=a; y*=a; z*=a; return *this; }
	inline tvec3& operator/=( T a ){ x/=a; y/=a; z/=a; return *this; }

	// casting
	inline operator T*(){ return &x; }
	inline operator const T*(){ return &x; }

	// array operator
	inline T& operator[]( int i ){ return (&r)[i]; }
	inline const T& operator[]( int i ) const { return (&r)[i]; }
	inline T& at( int i ){ return (&r)[i]; }
	inline const T& at( int i ) const { return (&r)[i]; }
	
	// unary operators
	inline tvec3 operator+(){ return tvec3(r, g, b); }
	inline tvec3 operator+() const { return tvec3(r, g, b); }
	inline tvec3 operator-(){ return tvec3(-r, -g, -b); }
	inline tvec3 operator-() const { return tvec3(-r, -g, -b); }

	// binary operators
	inline tvec3 operator+( const tvec3& v ) const { return tvec3(r+v.r, g+v.g, b+v.b); }
	inline tvec3 operator-( const tvec3& v ) const { return tvec3(r-v.r, g-v.g, b-v.b); }
	inline tvec3 operator*( const tvec3& v ) const { return tvec3(r*v.r, g*v.g, b*v.b); }
	inline tvec3 operator/( const tvec3& v ) const { return tvec3(r/v.r, g/v.g, b/v.b); }
	inline tvec3 operator+( T a ) const { return tvec3(r+a, g+a, b+a); }
	inline tvec3 operator-( T a ) const { return tvec3(r-a, g-a, b-a); }
	inline tvec3 operator*( T a ){ return tvec3(r*a, g*a, b*a); }
	inline tvec3 operator/( T a ){ return tvec3(r/a, g/a, b/a); }
		
	// length, normalize, dot product
	inline T length(){ return (T)(sqrt(r*r+g*g+b*b));}
	inline T length2(){ return (T)(r*r+g*g+b*b);}
	inline tvec3 normalize(){ return tvec3(r, g, b)/length(); }
	inline T dot( const tvec3& v ) const { return (T)(r*v.r+g*v.g+b*v.b); }

	// tvec3 only: cross product
	inline tvec3 operator^( tvec3& v ){ return tvec3( g*v.b-b*v.g, b*v.r-r*v.b, r*v.g-g*v.r); }
	inline tvec3 operator^( const tvec3& v ) const { return tvec3( g*v.b-b*v.g, b*v.r-r*v.b, r*v.g-g*v.r); }
	inline tvec3 cross( tvec3& v ){ return tvec3( g*v.b-b*v.g, b*v.r-r*v.b, r*v.g-g*v.r); }
	inline tvec3 cross( const tvec3& v ) const { return tvec3( g*v.b-b*v.g, b*v.r-r*v.b, r*v.g-g*v.r); }
};

template <class T> struct tvec4
{
	union { struct { T r, g, b, a; }; struct { T x, y, z, w; }; };

	// constructor/set
	tvec4(){ x=y=z=w=0; }
	tvec4( T a ){ x=y=z=w=a; }										inline void set( T a ){ x=y=z=w=a; }
	tvec4( T a, T b, T c, T d ){ x=a;y=b;z=c;w=d; }					inline void set( T a, T b, T c, T d ){ x=a;y=b;z=c;w=d; }
	tvec4( const tvec4& v ){ x=v.x;y=v.y;z=v.z;w=v.w; }				inline void set( const tvec4& v ){ x=v.x;y=v.y;z=v.z;w=v.w; }
	tvec4( const T* a ){ x=a[0];y=a[1];z=a[2];w=a[3]; }				inline void set( const T* a ){ x=a[0];y=a[1];z=a[2];w=a[3]; }
	tvec4( const tvec2<T>& v, T c, T d ){ x=v.x;y=v.y;z=c;w=d; }	inline void set( const tvec2<T>& v, T c, T d ){ x=v.x;y=v.y;z=c;w=d; }
	tvec4( T a, T b, const tvec2<T>& v ){ x=a;y=b;z=v.x;w=v.y; }	inline void set( T a, T b, const tvec2<T>& v ){ x=a;y=b;z=v.x;w=v.y; }	
	tvec4( const tvec3<T>& v, T d ){ x=v.x;y=v.y;z=v.z;w=d; }		inline void set( const tvec3<T>& v, T d ){ x=v.x;y=v.y;z=v.z;w=d; }
	tvec4( T a, const tvec3<T>& v ){ x=a;y=v.x;z=v.y;w=v.z; }		inline void set( T a, const tvec3<T>& v ){ x=a;y=v.x;z=v.y;w=v.z; }
	tvec4( const tvec2<T>& v1, const tvec2<T>& v2 ){ x=v1.x;y=v1.y;z=v2.x;w=v2.y; }
	inline void set( const tvec2<T>& v1, const tvec2<T>& v2 ){ x=v1.x;y=v1.y;z=v2.x;w=v2.y; }

	// assignment
	inline tvec4& operator=( T a ){ set(a); return *this; }
	inline tvec4& operator=( const T* a ){ set(a); return *this; }
	inline tvec4& operator+=( const tvec4& v ){ x+=v.x; y+=v.y; z+=v.z; w+=v.w; return *this; }
	inline tvec4& operator-=( const tvec4& v ){ x-=v.x; y-=v.y; z-=v.z; w-=v.w; return *this; }
	inline tvec4& operator*=( const tvec4& v ){ x*=v.x; y*=v.y; z*=v.z; w*=v.w; return *this; }
	inline tvec4& operator/=( const tvec4& v ){ x/=v.x; y/=v.y; z/=v.z; w/=v.w; return *this; }
	inline tvec4& operator+=( T a ){ x+=a; y+=a; z+=a; w+=a; return *this; }
	inline tvec4& operator-=( T a ){ x-=a; y-=a; z-=a; w-=a; return *this; }
	inline tvec4& operator*=( T a ){ x*=a; y*=a; z*=a; w*=a; return *this; }
	inline tvec4& operator/=( T a ){ x/=a; y/=a; z/=a; w/=a; return *this; }
	
	// casting
	inline operator T*(){ return &x; }
	inline operator const T*(){ return &x; }

	// array operator
	inline T& operator[]( int i ){ return (&r)[i]; }
	inline const T& operator[]( int i ) const { return (&r)[i]; }

	// unary operators
	inline tvec4 operator+(){ return tvec4(r, g, b, a); }
	inline tvec4 operator+() const { return tvec4(r, g, b, a); }
	inline tvec4 operator-(){ return tvec4(-r, -g, -b, -a); }
	inline tvec4 operator-() const { return tvec4(-r, -g, -b, -a); }

	// binary operators
	inline tvec4 operator+( const tvec4& v ) const { return tvec4(r+v.r, g+v.g, b+v.b, a+v.a); }
	inline tvec4 operator-( const tvec4& v ) const { return tvec4(r-v.r, g-v.g, b-v.b, a-v.a); }
	inline tvec4 operator*( const tvec4& v ) const { return tvec4(r*v.r, g*v.g, b*v.b, a*v.a); }
	inline tvec4 operator/( const tvec4& v ) const { return tvec4(r/v.r, g/v.g, b/v.b, a/v.a); }
	inline tvec4 operator+( T a ) const { return tvec4(r+a, g+a, b+a, this->a+a); }
	inline tvec4 operator-( T a ) const { return tvec4(r-a, g-a, b-a, this->a-a); }
	inline tvec4 operator*( T a ){ return tvec4(r*a, g*a, b*a, this->a*a); }
	inline tvec4 operator/( T a ){ return tvec4(r/a, g/a, b/a, this->a/a); }

	// length, normalize, dot product
	inline T length(){ return (T)(sqrt(r*r+g*g+b*b+a*a)); }
	inline tvec4 normalize(){ return tvec4(r, g, b, a)/length(); } 
	inline T dot( const tvec4& v ) const { return (T)(r*v.r+g*v.g+b*v.b+a*v.a); }
};

//*******************************************************************
// typedefs
typedef tvec2<float>	vec2;		typedef tvec3<float>	vec3;		typedef tvec4<float>	vec4;
typedef tvec2<int>		ivec2;		typedef tvec3<int>		ivec3;		typedef tvec4<int>		ivec4;

//*******************************************************************
// matrix 4x4: uses a standard row-major notation.
struct mat4
{
	union { float a[16]; struct {float _11,_12,_13,_14,_21,_22,_23,_24,_31,_32,_33,_34,_41,_42,_43,_44;}; };

	mat4(){ _12=_13=_14=_21=_23=_24=_31=_32=_34=_41=_42=_43=0.0f;_11=_22=_33=_44=1.0f; }
	mat4( float* f ){ memcpy(a,f,sizeof(float)*16); }
	mat4( float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24, float f31, float f32, float f33, float f34, float f41, float f42, float f43, float f44 ){_11=f11;_12=f12;_13=f13;_14=f14;_21=f21;_22=f22;_23=f23;_24=f24;_31=f31;_32=f32;_33=f33;_34=f34;_41=f41;_42=f42;_43=f43;_44=f44;}
	
	// casting
	inline operator float*(){ return a; }
	inline operator const float*() const { return a; }

	// array access operator
	inline float& operator[]( unsigned i ){ return a[i]; }
	inline float& operator[]( int i ){ return a[i]; }
	inline const float& operator[]( unsigned i ) const { return a[i]; }
	inline const float& operator[]( int i ) const { return a[i]; }
	
	// basic operation
	inline mat4& setIdentity(){ _12=_13=_14=_21=_23=_24=_31=_32=_34=_41=_42=_43=0.0f;_11=_22=_33=_44=1.0f; return *this; }
	inline mat4 transpose() const { return mat4(_11, _21, _31, _41, _12, _22, _32, _42, _13, _23, _33, _43, _14, _24, _34, _44); }

	// static
        static mat4 identity(){ return mat4().setIdentity(); }
	static mat4 translate( vec3& v ){ return mat4().setTranslate(v); }
	static mat4 translate( float x, float y, float z ){ return mat4().setTranslate(x,y,z); }
	static mat4 scale( vec3& v ){ return mat4().setScale(v); }
	static mat4 scale( float x, float y, float z ){ return mat4().setScale(x,y,z); }
	static mat4 rotateX( float theta ){ return mat4().setRotateX(theta); }
	static mat4 rotateY( float theta ){ return mat4().setRotateY(theta); }
	static mat4 rotateZ( float theta ){ return mat4().setRotateZ(theta); }
	static mat4 rotate( vec3& axis, float angle ){ return mat4().setRotate(axis,angle); }

	// binary operator overloading
	inline vec4 operator*( const vec4& v )
	{
		vec4 r1 = vec4(_11, _12, _13, _14);
		vec4 r2 = vec4(_21, _22, _23, _24);
		vec4 r3 = vec4(_31, _32, _33, _34);
		vec4 r4 = vec4(_41, _42, _43, _44);

		return vec4(r1.dot(v), r2.dot(v), r3.dot(v), r4.dot(v)); 
	}
	inline mat4 operator*( mat4& M )
	{
		vec4 r1 = vec4(_11, _12, _13, _14); vec4 c1 = vec4(M._11, M._21, M._31, M._41);
		vec4 r2 = vec4(_21, _22, _23, _24); vec4 c2 = vec4(M._12, M._22, M._32, M._42);
		vec4 r3 = vec4(_31, _32, _33, _34); vec4 c3 = vec4(M._13, M._23, M._33, M._43);
 		vec4 r4 = vec4(_41, _42, _43, _44); vec4 c4 = vec4(M._14, M._24, M._34, M._44);

		return mat4(	r1.dot(c1), r1.dot(c2), r1.dot(c3), r1.dot(c4), 
						r2.dot(c1), r2.dot(c2), r2.dot(c3), r2.dot(c4), 
						r3.dot(c1), r3.dot(c2), r3.dot(c3), r3.dot(c4), 
						r4.dot(c1), r4.dot(c2), r4.dot(c3), r4.dot(c4)	);
	}

	// row-major transformations
	inline mat4& setTranslate(vec3& v){ setIdentity(); _14=v.x; _24=v.y; _34=v.z; return *this; }
	inline mat4& setTranslate(float x,float y,float z){ setIdentity(); _14=x; _24=y; _34=z; return *this; }
	inline mat4& setScale(vec3& v){ setIdentity(); _11=v.x; _22=v.y; _33=v.z; return *this; }
	inline mat4& setScale(float x,float y,float z){ setIdentity(); _11=x; _22=y; _33=z; return *this; }
	inline mat4& setRotateX(float theta){ return setRotate(vec3(1,0,0),theta); }
	inline mat4& setRotateY(float theta){ return setRotate(vec3(0,1,0),theta); }
	inline mat4& setRotateZ(float theta){ return setRotate(vec3(0,0,1),theta); }
	inline mat4& setRotate( const vec3& axis, float angle )
	{
		float c=cos(angle), s=sin(angle), x=axis.x, y=axis.y, z=axis.z;
		a[0] = x*x*(1-c)+c;		a[1] = x*y*(1-c)-z*s;		a[2] = x*z*(1-c)+y*s;	a[3] = 0.0f;
		a[4] = x*y*(1-c)+z*s;	a[5] = y*y*(1-c)+c;			a[6] = y*z*(1-c)-x*s;	a[7] = 0.0f;
		a[8] = x*z*(1-c)-y*s;	a[9] = y*z*(1-c)+x*s;		a[10] = z*z*(1-c)+c;		a[11] = 0.0f;
		a[12] = 0;				a[13] = 0;					a[14] = 0;				a[15] = 1.0f;
		return *this;
	}
	static mat4 lookAt(vec3 eye, vec3 at, vec3 up){ return mat4().setLookAt(eye, at, up); }
	static mat4 perspective(float fovy, float aspectRatio, float dNear, float dFar){ return mat4().setPerspective(fovy, aspectRatio, dNear, dFar); }

	inline float determinant() const 
	{
		// ref: http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
		float det;
		
		det = _11*_22*_33*_44 + _11*_23*_34*_42 + _11*_24*_32*_43 + _12*_21*_34*_43
			+ _12*_23*_31*_44 + _12*_24*_33*_41	+ _13*_21*_32*_44 + _13*_22*_34*_41
			+ _13*_24*_31*_42 + _14*_21*_33*_42 + _14*_22*_31*_43 + _14*_23*_32*_41
			- _11*_22*_34*_43 - _11*_23*_32*_44 - _11*_24*_33*_42 - _12*_21*_33*_44
			- _12*_23*_34*_41 - _12*_24*_31*_43	- _13*_21*_34*_42 - _13*_22*_31*_44
			- _13*_24*_32*_41 - _14*_21*_32*_43 - _14*_22*_33*_41 - _14*_23*_31*_42;

		return det;
	}

	inline mat4 inverse() const 
	{
		// ref: http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
		float det=determinant(); if( det==0 ) printf( "mat4::inverse() might be singular.\n" );
		
		float b11, b12, b13, b14, b21, b22, b23, b24, b31, b32, b33, b34, b41, b42, b43, b44;

		b11 = (_22*_33*_44 + _23*_34*_42 + _24*_32*_43 - _22*_34*_43 - _23*_32*_44 - _24*_33*_42)/det;
		b12 = (_12*_34*_43 + _13*_32*_44 + _14*_33*_42 - _12*_33*_44 - _13*_34*_42 - _14*_32*_43)/det;
		b13 = (_12*_23*_44 + _13*_24*_42 + _14*_22*_43 - _12*_24*_43 - _13*_22*_44 - _14*_23*_42)/det;
		b14 = (_12*_24*_33 + _13*_22*_34 + _14*_23*_32 - _12*_23*_34 - _13*_24*_32 - _14*_22*_33)/det;
		b21 = (_21*_34*_43 + _23*_31*_44 + _24*_33*_41 - _21*_33*_44 - _23*_34*_41 - _24*_31*_43)/det;
		b22 = (_11*_33*_44 + _13*_34*_41 + _14*_31*_43 - _11*_34*_43 - _13*_31*_44 - _14*_33*_41)/det;
		b23 = (_11*_24*_43 + _13*_21*_44 + _14*_23*_41 - _11*_23*_44 - _13*_24*_41 - _14*_21*_43)/det;
		b24 = (_11*_23*_34 + _13*_24*_31 + _14*_21*_33 - _11*_24*_33 - _13*_21*_34 - _14*_23*_31)/det;
		b31 = (_21*_32*_44 + _22*_34*_41 + _24*_31*_42 - _21*_34*_42 - _22*_31*_44 - _24*_32*_41)/det;
		b32 = (_11*_34*_42 + _12*_31*_44 + _14*_32*_41 - _11*_32*_44 - _12*_34*_41 - _14*_31*_42)/det;
		b33 = (_11*_22*_44 + _12*_24*_41 + _14*_21*_42 - _11*_24*_42 - _12*_21*_44 - _14*_22*_41)/det;
		b34 = (_11*_24*_32 + _12*_21*_34 + _14*_22*_31 - _11*_22*_34 - _12*_24*_31 - _14*_21*_32)/det;
		b41 = (_21*_33*_42 + _22*_31*_43 + _23*_32*_41 - _21*_32*_43 - _22*_33*_41 - _23*_31*_42)/det;
		b42 = (_11*_32*_43 + _12*_33*_41 + _13*_31*_42 - _11*_33*_42 - _12*_31*_43 - _13*_32*_41)/det;
		b43 = (_11*_23*_42 + _12*_21*_43 + _13*_22*_41 - _11*_22*_43 - _12*_23*_41 - _13*_21*_42)/det;
		b44 = (_11*_22*_33 + _12*_23*_31 + _13*_21*_32 - _11*_23*_32 - _12*_21*_33 - _13*_22*_31)/det;

		return mat4( b11, b12, b13, b14, b21, b22, b23, b24, b31, b32, b33, b34, b41, b42, b43, b44 );
	}
	
	mat4& setLookAt(vec3 eye, vec3 at, vec3 up)
	{
		setIdentity();
		// define camera frame.
		vec3 n = (eye - at).normalize();
		vec3 u = (up ^ n).normalize();
		vec3 v = (n ^ u).normalize();

		// calculate lookAt matrix
		_11 = u.x;  _12 = u.y;  _13 = u.z;  _14 = -u.dot(eye);
		_21 = v.x;  _22 = v.y;  _23 = v.z;  _24 = -v.dot(eye);
		_31 = n.x;  _32 = n.y;  _33 = n.z;  _34 = -n.dot(eye);
		
		return *this;
	};
	
	mat4& setPerspective(float fovy, float aspectRatio, float dNear, float dFar)
	{
		setIdentity();
		_22 = 1 / tan(fovy / 2.0f);
		_11 = _22 / aspectRatio;
		_33 = (dNear + dFar) / (dNear - dFar);
		_34 = (2 * dNear * dFar) / (dNear - dFar);
		_43 = -1;
		_44 = 0;

		return *this;
	}
};

//*******************************************************************
// additional utility functions
inline vec2 operator+( float f, vec2& v ){ return v+f; }
inline vec3 operator+( float f, vec3& v ){ return v+f; }
inline vec4 operator+( float f, vec4& v ){ return v+f; }
inline vec2 operator-( float f, vec2& v ){ return -v+f; }
inline vec3 operator-( float f, vec3& v ){ return -v+f; }
inline vec4 operator-( float f, vec4& v ){ return -v+f; }
inline vec2 operator*( float f, vec2& v ){ return v*f; }
inline vec3 operator*( float f, vec3& v ){ return v*f; }
inline vec4 operator*( float f, vec4& v ){ return v*f; }
inline float dot(vec2& v1,vec2& v2){ return v1.dot(v2); }
inline float dot(vec3& v1,vec3& v2){ return v1.dot(v2); }
inline float dot(vec4& v1,vec4& v2){ return v1.dot(v2); }

//*******************************************************************
// common macros
#ifndef _CRT_SECURE_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef PI
	#define PI 3.141592653589793f
#endif
#ifndef max
	#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef min
	#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef clamp
	#define clamp(value,vmin,vmax) (max(vmin,min(vmax,value)))
#endif
#ifndef isnan
	#define	isnan(x) (x!=x)
#endif
