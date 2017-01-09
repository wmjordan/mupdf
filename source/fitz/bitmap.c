#include "mupdf/fitz.h"

static const unsigned char pkm[256*8] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
	0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00,
	0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
	0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF,
	0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
	0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
	0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
	0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
	0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
	0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00,
	0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
	0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
	0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

fz_bitmap *
fz_new_bitmap(fz_context *ctx, int w, int h, int n, int xres, int yres)
{
	fz_bitmap *bit;

	bit = fz_malloc_struct(ctx, fz_bitmap);
	bit->refs = 1;
	bit->w = w;
	bit->h = h;
	bit->n = n;
	bit->xres = xres;
	bit->yres = yres;
	/* Span is 32 bit aligned. We may want to make this 64 bit if we
	 * use SSE2 etc. */
	bit->stride = ((n * w + 31) & ~31) >> 3;

	bit->samples = fz_malloc_array(ctx, h, bit->stride);

	return bit;
}

fz_bitmap *
fz_keep_bitmap(fz_context *ctx, fz_bitmap *bit)
{
	return fz_keep_imp(ctx, bit, &bit->refs);
}

void
fz_drop_bitmap(fz_context *ctx, fz_bitmap *bit)
{
	if (fz_drop_imp(ctx, bit, &bit->refs))
	{
		fz_free(ctx, bit->samples);
		fz_free(ctx, bit);
	}
}

void
fz_clear_bitmap(fz_context *ctx, fz_bitmap *bit)
{
	memset(bit->samples, 0, bit->stride * bit->h);
}

static void
pbm_write_header(fz_context *ctx, fz_band_writer *writer)
{
	fz_output *out = writer->out;
	int w = writer->w;
	int h = writer->h;

	fz_printf(ctx, out, "P4\n%d %d\n", w, h);
}

static void
pkm_write_header(fz_context *ctx, fz_band_writer *writer)
{
	fz_output *out = writer->out;
	int w = writer->w;
	int h = writer->h;

	fz_printf(ctx, out, "P7\nWIDTH %d\nHEIGHT %d\nDEPTH 4\nMAXVAL 255\nTUPLTYPE CMYK\nENDHDR\n", w, h);
}

void
fz_write_bitmap_as_pbm(fz_context *ctx, fz_output *out, fz_bitmap *bitmap)
{
	fz_band_writer *writer = fz_new_pbm_band_writer(ctx, out);

	fz_write_header(ctx, writer, bitmap->w, bitmap->h, 1, 0, 0, 0, 1);
	fz_write_band(ctx, writer, bitmap->stride, 0, bitmap->h, bitmap->samples);
	fz_write_trailer(ctx, writer);
	fz_drop_band_writer(ctx, writer);
}

void
fz_write_bitmap_as_pkm(fz_context *ctx, fz_output *out, fz_bitmap *bitmap)
{
	fz_band_writer *writer = fz_new_pkm_band_writer(ctx, out);

	fz_write_header(ctx, writer, bitmap->w, bitmap->h, 1, 0, 0, 0, 1);
	fz_write_band(ctx, writer, bitmap->stride, 0, bitmap->h, bitmap->samples);
	fz_write_trailer(ctx, writer);
	fz_drop_band_writer(ctx, writer);
}

static void
pbm_write_band(fz_context *ctx, fz_band_writer *writer, int stride, int band_start, int band_height, const unsigned char *p)
{
	fz_output *out = writer->out;
	int w = writer->w;
	int h = writer->h;
	int n = writer->n;
	int bytestride;
	int end = band_start + band_height;

	if (n != 1)
		fz_throw(ctx, FZ_ERROR_GENERIC, "too many color components in bitmap");

	if (end > h)
		end = h;
	end -= band_start;

	bytestride = (w + 7) >> 3;
	while (end--)
	{
		fz_write(ctx, out, p, bytestride);
		p += stride;
	}
}

static void
pkm_write_band(fz_context *ctx, fz_band_writer *writer, int stride, int band_start, int band_height, const unsigned char *p)
{
	fz_output *out = writer->out;
	int w = writer->w;
	int h = writer->h;
	int n = writer->n;
	int bytestride;
	int end = band_start + band_height;

	if (n != 4)
		fz_throw(ctx, FZ_ERROR_GENERIC, "wrong number of color components in bitmap");

	if (end > h)
		end = h;
	end -= band_start;

	bytestride = stride - (w>>1);
	while (end--)
	{
		int ww = w-1;
		while (ww > 0)
		{
			fz_write(ctx, out, &pkm[8 * *p++], 8);
			ww -= 2;
		}
		if (ww == 0)
			fz_write(ctx, out, &pkm[8 * *p], 4);
		p += bytestride;
	}
}

fz_band_writer *fz_new_pbm_band_writer(fz_context *ctx, fz_output *out)
{
	fz_band_writer *writer = fz_new_band_writer(ctx, fz_band_writer, out);

	writer->header = pbm_write_header;
	writer->band = pbm_write_band;

	return writer;
}

fz_band_writer *fz_new_pkm_band_writer(fz_context *ctx, fz_output *out)
{
	fz_band_writer *writer = fz_new_band_writer(ctx, fz_band_writer, out);

	writer->header = pkm_write_header;
	writer->band = pkm_write_band;

	return writer;
}

void
fz_save_bitmap_as_pbm(fz_context *ctx, fz_bitmap *bitmap, char *filename)
{
	fz_output *out = fz_new_output_with_path(ctx, filename, 0);
	fz_try(ctx)
		fz_write_bitmap_as_pbm(ctx, out, bitmap);
	fz_always(ctx)
		fz_drop_output(ctx, out);
	fz_catch(ctx)
		fz_rethrow(ctx);
}

void
fz_save_bitmap_as_pkm(fz_context *ctx, fz_bitmap *bitmap, char *filename)
{
	fz_output *out = fz_new_output_with_path(ctx, filename, 0);
	fz_try(ctx)
		fz_write_bitmap_as_pkm(ctx, out, bitmap);
	fz_always(ctx)
		fz_drop_output(ctx, out);
	fz_catch(ctx)
		fz_rethrow(ctx);
}

void fz_bitmap_details(fz_bitmap *bit, int *w, int *h, int *n, int *stride)
{
	if (!bit)
	{
		if (w)
			*w = 0;
		if (h)
			*h = 0;
		if (n)
			*n = 0;
		if (stride)
			*stride = 0;
		return;
	}
	if (w)
		*w = bit->w;
	if (h)
		*h = bit->h;
	if (n)
		*n = bit->n;
	if (stride)
		*stride = bit->stride;
}
