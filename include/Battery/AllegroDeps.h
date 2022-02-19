#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN		// Prevent winsock.h from being included by windows.h
#endif

#ifndef NOMINMAX
#define NOMINMAX		// Prevent windows.h from defining min and max
#endif

#include "Battery/Core/Config.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_windows.h>
#include <allegro5/allegro_memfile.h>

#ifdef RegisterClipboardFormat
#undef RegisterClipboardFormat
#endif

#ifdef RemoveDirectory
#undef RemoveDirectory
#endif

#ifdef MoveFile
#undef MoveFile
#endif
