#pragma once

#include "GL/glew.h"		// glew.sourceforge.net
#include "GL/freeglut.h"	// freeglut.sourceforge.net
#include <stdio.h>

#pragma comment( lib, "OpenGL32.lib" )	// link OpenGL32 library
#pragma comment( lib, "glew32.lib" )	// link glew library
#pragma comment( lib, "freeglut.lib" )	// link freeglut library

// enforce not to use /MD or /MDd flag
#ifdef _DLL
	#ifdef _DEBUG
		#error use /MTd at Configuration -> C/C++ -> Code Generation -> Run-time Library
	#else
		#error use /MT at Configuration -> C/C++ -> Code Generation -> Run-time Library	
	#endif
#endif

//*******************************************************************
// utility functions
inline char* readShader( const char* filePath )
{
	// get the full path of shader file
	char moduleFilePath[_MAX_PATH]; GetModuleFileNameA( 0, moduleFilePath, _MAX_PATH );
	char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	_splitpath_s( moduleFilePath, drive,_MAX_DRIVE,dir,_MAX_DIR,fname,_MAX_FNAME,ext,_MAX_EXT);
	char shaderFilePath[_MAX_PATH]; sprintf_s( shaderFilePath, "%s%s%s", drive, dir, filePath );
	
	// get the full path of a shader file
	FILE* fp = fopen( shaderFilePath, "rb" ); if(fp==NULL){ printf( "Unable to open %s\n", shaderFilePath ); return NULL; }
	fseek( fp, 0L, SEEK_END );
	size_t fileSize = ftell(fp);
	fseek( fp, 0L, SEEK_SET );
	char* strShader = (char*) malloc( (fileSize+1)*sizeof(char) );
	fread( strShader, sizeof(char), fileSize, fp );
	fclose(fp);

	strShader[fileSize] = NULL;
	return strShader;
}

inline bool checkShader( GLuint shaderID, const char* shaderName )
{
	const int MAX_LOG_LENGTH=1024;
	static char msg[MAX_LOG_LENGTH] = {NULL};
	GLint shaderInfoLogLength;
	bool bLogExists = false;

	glGetShaderInfoLog( shaderID, MAX_LOG_LENGTH, &shaderInfoLogLength, msg );
	if( bLogExists=(shaderInfoLogLength>1&&shaderInfoLogLength<=MAX_LOG_LENGTH) )
		printf( "[Shader Log: %s]\n%s\n", shaderName, msg );

	GLint shaderCompileStatus; glGetShaderiv( shaderID, GL_COMPILE_STATUS, &shaderCompileStatus);
	if(shaderCompileStatus==GL_TRUE) return true;
	
	glDeleteShader( shaderID );
	return false;
}

inline bool checkProgram( GLuint programID, const char* programName )
{
	static const int MAX_LOG_LENGTH=1024;
	static char msg[MAX_LOG_LENGTH] = {NULL};
	GLint programInfoLogLength;
	bool bLogExists = false;

	glGetProgramInfoLog( programID, MAX_LOG_LENGTH, &programInfoLogLength, msg );
	if( bLogExists=(programInfoLogLength>1&&programInfoLogLength<=MAX_LOG_LENGTH) )
		printf( "[Program Log: %s]\n%s\n", programName, msg );

	GLint programLinkStatus; glGetProgramiv( programID, GL_LINK_STATUS, &programLinkStatus);
	if(programLinkStatus!=GL_TRUE){ glDeleteProgram(programID); return false; }

	glValidateProgram( programID );
	glGetProgramInfoLog( programID, MAX_LOG_LENGTH, &programInfoLogLength, msg );
	if( bLogExists=(programInfoLogLength>1&&programInfoLogLength<=MAX_LOG_LENGTH) )
		printf( "[Program Log: %s]\n%s\n", programName, msg );

	GLint programValidateStatus; glGetProgramiv( programID, GL_VALIDATE_STATUS, &programValidateStatus);
	if( programValidateStatus!=GL_TRUE ){ glDeleteProgram(programID); return false; }

	return true;
}

inline bool initExtensions()
{
	// get the full path of the current executable and change the working directory
	char moduleFilePath[_MAX_PATH]; GetModuleFileNameA( 0, moduleFilePath, _MAX_PATH );
	char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	_splitpath_s( moduleFilePath, drive,_MAX_DRIVE,dir,_MAX_DIR,fname,_MAX_FNAME,ext,_MAX_EXT);
	char moduleDir[_MAX_PATH]; sprintf_s( moduleDir, "%s%s", drive, dir );
	SetCurrentDirectoryA( moduleDir );

	// load and register GL extensions using GLEW
	int e; if((e=glewInit())!=GLEW_OK){ printf( "Failed to init GLEW\nError: %s\n", glewGetErrorString(e) ); return false; }

	// check GL version
	int verMajor; glGetIntegerv(GL_MAJOR_VERSION, &verMajor); // major = 3
	int verMinor; glGetIntegerv(GL_MINOR_VERSION, &verMinor); // minor = 2
	while(verMinor>10) verMinor/=10;
	printf( "GL: Using OpenGL %d.%d", verMajor, verMinor );
	int version = verMajor*10+verMinor;

	// check GLSL version
	const char* strGLSLver = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	if(strGLSLver==NULL) printf( "Warning: Unable to get glGetString(GL_SHADING_LANGUAGE_VERSION)\n" );
	float GLSLversion = strGLSLver?float(atof(strGLSLver)):0.0f;
	if( GLSLversion < 1.1f ){ printf( "GLSL %.1f not supports shader programs. Please update your platform\n", GLSLversion ); return false; }
	printf( " and GLSL %.1f\n\n", GLSLversion );

	// check supported extensions
	#define CHECK_EXTENSION(ext) if(!glewGetExtension("GL_ARB_"#ext)){ printf( "-------------------------\nGLEW: GL_ARB_" #ext " not supported.\n" ); return false; }
	CHECK_EXTENSION( shading_language_100 );	// check your platform supports GLSL
	CHECK_EXTENSION( vertex_buffer_object );	// BindBuffers, DeleteBuffers, GenBuffers, IsBuffer, BufferData, BufferSubData, GenBufferSubData, ...
	CHECK_EXTENSION( vertex_shader );			// functions related to vertex shaders
	CHECK_EXTENSION( fragment_shader );			// functions related to fragment shaders
	CHECK_EXTENSION( shader_objects );			// functions related to program and shaders
	#undef CHECK_EXTENSION

	return true;
}