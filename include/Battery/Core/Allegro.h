#pragma once

#include "Battery/Core/Config.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_native_dialog.h>

//#include <allegro5/allegro_windows.h>

#ifdef RegisterClipboardFormat
#undef RegisterClipboardFormat
#endif

#ifdef RemoveDirectory
#undef RemoveDirectory
#endif

#ifdef MoveFile
#undef MoveFile
#endif