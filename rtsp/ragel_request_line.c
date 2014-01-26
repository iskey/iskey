
/* #line 1 "src/network/ragel_request_line.rl" */
/* -*- c -*- */
/* *
 * This file is part of Feng
 *
 * Copyright (C) 2009 by LScube team <team@lscube.org>
 * See AUTHORS for more details
 *
 * feng is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * feng is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with feng; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * */

#include "rtsp.h"

size_t ragel_parse_request_line(const char *msg, const size_t length, RFC822_Request *req) {
    int cs, top, stack[2];
    const char *p = msg, *pe = p + length, *s = NULL, *pp;
    int method_code = RTSP_Method__Invalid;
    RFC822_Protocol protocol_code = RFC822_Protocol_Invalid;

    const char *method_str = NULL;
    size_t method_len = 0;

    const char *protocol_str = NULL;
    size_t protocol_len = 0;

    const char *object_str = NULL;
    size_t object_len = 0;

    
/* #line 45 "src/network/ragel_request_line.c" */
static const char _request_line_actions[] = {
	0, 1, 15, 1, 17, 1, 18, 1, 
	25, 2, 5, 19, 2, 12, 20, 2, 
	15, 18, 2, 15, 22, 2, 16, 21, 
	3, 5, 6, 19, 3, 5, 7, 19, 
	3, 5, 8, 19, 3, 5, 9, 19, 
	3, 5, 10, 19, 3, 5, 11, 19, 
	3, 12, 13, 20, 3, 12, 14, 20, 
	3, 17, 0, 23, 3, 17, 1, 23, 
	3, 17, 2, 24, 3, 17, 3, 24, 
	3, 17, 4, 24
};

static const short _request_line_key_offsets[] = {
	0, 0, 10, 21, 24, 33, 36, 44, 
	51, 55, 62, 67, 69, 78, 87, 96, 
	104, 112, 116, 123, 128, 132, 141, 146, 
	151, 160, 169, 178, 186, 194, 198, 205, 
	210, 214, 222, 227, 242, 253, 265, 277, 
	289, 301, 313, 325, 337, 348, 360, 372, 
	384, 396, 408, 420, 431, 444, 456, 468, 
	480, 491, 503, 515, 526, 538, 550, 562, 
	574, 585, 597, 609, 621, 633, 645, 657, 
	669, 680, 692, 703, 715, 727, 738, 750, 
	762, 774, 785, 785, 785
};

static const char _request_line_trans_keys[] = {
	95, 126, 45, 46, 48, 57, 65, 90, 
	97, 122, 32, 95, 126, 45, 46, 48, 
	57, 65, 90, 97, 122, 32, 33, 126, 
	32, 72, 82, 33, 64, 65, 90, 91, 
	126, 32, 33, 126, 32, 47, 33, 64, 
	65, 90, 91, 126, 32, 33, 47, 48, 
	57, 58, 126, 32, 46, 33, 126, 32, 
	33, 47, 48, 57, 58, 126, 10, 13, 
	32, 33, 126, 10, 13, 32, 47, 84, 
	33, 64, 65, 90, 91, 126, 32, 47, 
	84, 33, 64, 65, 90, 91, 126, 32, 
	47, 80, 33, 64, 65, 90, 91, 126, 
	32, 47, 33, 64, 65, 90, 91, 126, 
	32, 49, 33, 47, 48, 57, 58, 126, 
	32, 46, 33, 126, 32, 33, 47, 48, 
	57, 58, 126, 10, 13, 32, 33, 126, 
	32, 46, 33, 126, 32, 48, 49, 33, 
	47, 50, 57, 58, 126, 10, 13, 32, 
	33, 126, 10, 13, 32, 33, 126, 32, 
	47, 84, 33, 64, 65, 90, 91, 126, 
	32, 47, 83, 33, 64, 65, 90, 91, 
	126, 32, 47, 80, 33, 64, 65, 90, 
	91, 126, 32, 47, 33, 64, 65, 90, 
	91, 126, 32, 49, 33, 47, 48, 57, 
	58, 126, 32, 46, 33, 126, 32, 33, 
	47, 48, 57, 58, 126, 10, 13, 32, 
	33, 126, 32, 46, 33, 126, 32, 48, 
	33, 47, 49, 57, 58, 126, 10, 13, 
	32, 33, 126, 68, 79, 80, 83, 84, 
	95, 126, 45, 46, 48, 57, 65, 90, 
	97, 122, 32, 95, 126, 45, 46, 48, 
	57, 65, 90, 97, 122, 32, 69, 95, 
	126, 45, 46, 48, 57, 65, 90, 97, 
	122, 32, 83, 95, 126, 45, 46, 48, 
	57, 65, 90, 97, 122, 32, 67, 95, 
	126, 45, 46, 48, 57, 65, 90, 97, 
	122, 32, 82, 95, 126, 45, 46, 48, 
	57, 65, 90, 97, 122, 32, 73, 95, 
	126, 45, 46, 48, 57, 65, 90, 97, 
	122, 32, 66, 95, 126, 45, 46, 48, 
	57, 65, 90, 97, 122, 32, 69, 95, 
	126, 45, 46, 48, 57, 65, 90, 97, 
	122, 32, 95, 126, 45, 46, 48, 57, 
	65, 90, 97, 122, 32, 80, 95, 126, 
	45, 46, 48, 57, 65, 90, 97, 122, 
	32, 84, 95, 126, 45, 46, 48, 57, 
	65, 90, 97, 122, 32, 73, 95, 126, 
	45, 46, 48, 57, 65, 90, 97, 122, 
	32, 79, 95, 126, 45, 46, 48, 57, 
	65, 90, 97, 122, 32, 78, 95, 126, 
	45, 46, 48, 57, 65, 90, 97, 122, 
	32, 83, 95, 126, 45, 46, 48, 57, 
	65, 90, 97, 122, 32, 95, 126, 45, 
	46, 48, 57, 65, 90, 97, 122, 32, 
	65, 76, 95, 126, 45, 46, 48, 57, 
	66, 90, 97, 122, 32, 85, 95, 126, 
	45, 46, 48, 57, 65, 90, 97, 122, 
	32, 83, 95, 126, 45, 46, 48, 57, 
	65, 90, 97, 122, 32, 69, 95, 126, 
	45, 46, 48, 57, 65, 90, 97, 122, 
	32, 95, 126, 45, 46, 48, 57, 65, 
	90, 97, 122, 32, 65, 95, 126, 45, 
	46, 48, 57, 66, 90, 97, 122, 32, 
	89, 95, 126, 45, 46, 48, 57, 65, 
	90, 97, 122, 32, 95, 126, 45, 46, 
	48, 57, 65, 90, 97, 122, 32, 69, 
	95, 126, 45, 46, 48, 57, 65, 90, 
	97, 122, 32, 84, 95, 126, 45, 46, 
	48, 57, 65, 90, 97, 122, 32, 85, 
	95, 126, 45, 46, 48, 57, 65, 90, 
	97, 122, 32, 80, 95, 126, 45, 46, 
	48, 57, 65, 90, 97, 122, 32, 95, 
	126, 45, 46, 48, 57, 65, 90, 97, 
	122, 32, 69, 95, 126, 45, 46, 48, 
	57, 65, 90, 97, 122, 32, 65, 95, 
	126, 45, 46, 48, 57, 66, 90, 97, 
	122, 32, 82, 95, 126, 45, 46, 48, 
	57, 65, 90, 97, 122, 32, 68, 95, 
	126, 45, 46, 48, 57, 65, 90, 97, 
	122, 32, 79, 95, 126, 45, 46, 48, 
	57, 65, 90, 97, 122, 32, 87, 95, 
	126, 45, 46, 48, 57, 65, 90, 97, 
	122, 32, 78, 95, 126, 45, 46, 48, 
	57, 65, 90, 97, 122, 32, 95, 126, 
	45, 46, 48, 57, 65, 90, 97, 122, 
	71, 80, 95, 126, 45, 46, 48, 57, 
	65, 90, 97, 122, 32, 95, 126, 45, 
	46, 48, 57, 65, 90, 97, 122, 32, 
	69, 95, 126, 45, 46, 48, 57, 65, 
	90, 97, 122, 32, 84, 95, 126, 45, 
	46, 48, 57, 65, 90, 97, 122, 32, 
	95, 126, 45, 46, 48, 57, 65, 90, 
	97, 122, 32, 79, 95, 126, 45, 46, 
	48, 57, 65, 90, 97, 122, 32, 83, 
	95, 126, 45, 46, 48, 57, 65, 90, 
	97, 122, 32, 84, 95, 126, 45, 46, 
	48, 57, 65, 90, 97, 122, 32, 95, 
	126, 45, 46, 48, 57, 65, 90, 97, 
	122, 0
};

static const char _request_line_single_lengths[] = {
	0, 2, 3, 1, 3, 1, 2, 1, 
	2, 1, 3, 2, 3, 3, 3, 2, 
	2, 2, 1, 3, 2, 3, 3, 3, 
	3, 3, 3, 2, 2, 2, 1, 3, 
	2, 2, 3, 7, 3, 4, 4, 4, 
	4, 4, 4, 4, 3, 4, 4, 4, 
	4, 4, 4, 3, 5, 4, 4, 4, 
	3, 4, 4, 3, 4, 4, 4, 4, 
	3, 4, 4, 4, 4, 4, 4, 4, 
	3, 4, 3, 4, 4, 3, 4, 4, 
	4, 3, 0, 0, 0
};

static const char _request_line_range_lengths[] = {
	0, 4, 4, 1, 3, 1, 3, 3, 
	1, 3, 1, 0, 3, 3, 3, 3, 
	3, 1, 3, 1, 1, 3, 1, 1, 
	3, 3, 3, 3, 3, 1, 3, 1, 
	1, 3, 1, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 0, 0, 0
};

static const short _request_line_index_offsets[] = {
	0, 0, 7, 15, 18, 25, 28, 34, 
	39, 43, 48, 53, 56, 63, 70, 77, 
	83, 89, 93, 98, 103, 107, 114, 119, 
	124, 131, 138, 145, 151, 157, 161, 166, 
	171, 175, 181, 186, 198, 206, 215, 224, 
	233, 242, 251, 260, 269, 277, 286, 295, 
	304, 313, 322, 331, 339, 349, 358, 367, 
	376, 384, 393, 402, 410, 419, 428, 437, 
	446, 454, 463, 472, 481, 490, 499, 508, 
	517, 525, 534, 542, 551, 560, 568, 577, 
	586, 595, 603, 604, 605
};

static const char _request_line_indicies[] = {
	0, 0, 0, 0, 0, 0, 1, 2, 
	3, 3, 3, 3, 3, 3, 1, 4, 
	5, 1, 6, 9, 10, 7, 8, 7, 
	1, 6, 7, 1, 6, 11, 7, 12, 
	7, 1, 6, 7, 13, 7, 1, 6, 
	14, 7, 1, 6, 7, 15, 7, 1, 
	16, 17, 6, 7, 1, 18, 19, 1, 
	6, 11, 20, 7, 12, 7, 1, 6, 
	11, 21, 7, 12, 7, 1, 6, 11, 
	22, 7, 12, 7, 1, 6, 23, 7, 
	12, 7, 1, 6, 25, 7, 24, 7, 
	1, 6, 26, 7, 1, 6, 7, 27, 
	7, 1, 28, 29, 6, 7, 1, 6, 
	30, 7, 1, 6, 31, 32, 7, 15, 
	7, 1, 33, 34, 6, 7, 1, 35, 
	36, 6, 7, 1, 6, 11, 37, 7, 
	12, 7, 1, 6, 11, 38, 7, 12, 
	7, 1, 6, 11, 39, 7, 12, 7, 
	1, 6, 40, 7, 12, 7, 1, 6, 
	42, 7, 41, 7, 1, 6, 43, 7, 
	1, 6, 7, 44, 7, 1, 45, 46, 
	6, 7, 1, 6, 47, 7, 1, 6, 
	48, 7, 15, 7, 1, 49, 50, 6, 
	7, 1, 52, 53, 54, 55, 56, 51, 
	51, 51, 51, 51, 51, 1, 57, 51, 
	51, 51, 51, 51, 51, 1, 57, 58, 
	51, 51, 51, 51, 51, 51, 1, 57, 
	59, 51, 51, 51, 51, 51, 51, 1, 
	57, 60, 51, 51, 51, 51, 51, 51, 
	1, 57, 61, 51, 51, 51, 51, 51, 
	51, 1, 57, 62, 51, 51, 51, 51, 
	51, 51, 1, 57, 63, 51, 51, 51, 
	51, 51, 51, 1, 57, 64, 51, 51, 
	51, 51, 51, 51, 1, 65, 51, 51, 
	51, 51, 51, 51, 1, 57, 66, 51, 
	51, 51, 51, 51, 51, 1, 57, 67, 
	51, 51, 51, 51, 51, 51, 1, 57, 
	68, 51, 51, 51, 51, 51, 51, 1, 
	57, 69, 51, 51, 51, 51, 51, 51, 
	1, 57, 70, 51, 51, 51, 51, 51, 
	51, 1, 57, 71, 51, 51, 51, 51, 
	51, 51, 1, 72, 51, 51, 51, 51, 
	51, 51, 1, 57, 73, 74, 51, 51, 
	51, 51, 51, 51, 1, 57, 75, 51, 
	51, 51, 51, 51, 51, 1, 57, 76, 
	51, 51, 51, 51, 51, 51, 1, 57, 
	77, 51, 51, 51, 51, 51, 51, 1, 
	78, 51, 51, 51, 51, 51, 51, 1, 
	57, 79, 51, 51, 51, 51, 51, 51, 
	1, 57, 80, 51, 51, 51, 51, 51, 
	51, 1, 81, 51, 51, 51, 51, 51, 
	51, 1, 57, 82, 51, 51, 51, 51, 
	51, 51, 1, 57, 83, 51, 51, 51, 
	51, 51, 51, 1, 57, 84, 51, 51, 
	51, 51, 51, 51, 1, 57, 85, 51, 
	51, 51, 51, 51, 51, 1, 86, 51, 
	51, 51, 51, 51, 51, 1, 57, 87, 
	51, 51, 51, 51, 51, 51, 1, 57, 
	88, 51, 51, 51, 51, 51, 51, 1, 
	57, 89, 51, 51, 51, 51, 51, 51, 
	1, 57, 90, 51, 51, 51, 51, 51, 
	51, 1, 57, 91, 51, 51, 51, 51, 
	51, 51, 1, 57, 92, 51, 51, 51, 
	51, 51, 51, 1, 57, 93, 51, 51, 
	51, 51, 51, 51, 1, 94, 51, 51, 
	51, 51, 51, 51, 1, 96, 97, 95, 
	95, 95, 95, 95, 95, 1, 98, 95, 
	95, 95, 95, 95, 95, 1, 98, 99, 
	95, 95, 95, 95, 95, 95, 1, 98, 
	100, 95, 95, 95, 95, 95, 95, 1, 
	101, 95, 95, 95, 95, 95, 95, 1, 
	98, 102, 95, 95, 95, 95, 95, 95, 
	1, 98, 103, 95, 95, 95, 95, 95, 
	95, 1, 98, 104, 95, 95, 95, 95, 
	95, 95, 1, 105, 95, 95, 95, 95, 
	95, 95, 1, 1, 1, 1, 0
};

static const char _request_line_trans_targs[] = {
	2, 0, 3, 2, 4, 5, 4, 5, 
	6, 12, 24, 7, 6, 8, 9, 10, 
	82, 11, 82, 11, 13, 14, 15, 16, 
	17, 20, 18, 19, 82, 11, 21, 22, 
	23, 82, 11, 82, 11, 25, 26, 27, 
	28, 29, 32, 30, 31, 82, 11, 33, 
	34, 82, 11, 36, 37, 45, 52, 60, 
	65, 83, 38, 39, 40, 41, 42, 43, 
	44, 83, 46, 47, 48, 49, 50, 51, 
	83, 53, 57, 54, 55, 56, 83, 58, 
	59, 83, 61, 62, 63, 64, 83, 66, 
	67, 68, 69, 70, 71, 72, 83, 74, 
	75, 78, 84, 76, 77, 84, 79, 80, 
	81, 84
};

static const char _request_line_trans_actions[] = {
	1, 0, 21, 0, 15, 1, 5, 0, 
	18, 18, 18, 0, 0, 0, 0, 0, 
	3, 3, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 72, 72, 0, 0, 
	0, 64, 64, 68, 68, 0, 0, 0, 
	0, 0, 0, 0, 0, 60, 60, 0, 
	0, 56, 56, 0, 0, 0, 0, 0, 
	0, 9, 0, 0, 0, 0, 0, 0, 
	0, 24, 0, 0, 0, 0, 0, 0, 
	28, 0, 0, 0, 0, 0, 32, 0, 
	0, 36, 0, 0, 0, 0, 40, 0, 
	0, 0, 0, 0, 0, 0, 44, 0, 
	0, 0, 12, 0, 0, 48, 0, 0, 
	0, 52
};

static const char _request_line_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 7, 0, 0
};

static const int request_line_start = 1;
static const int request_line_first_final = 82;

static const int request_line_en_RTSP_SL_Method = 35;
static const int request_line_en_HTTP_SL_Method = 73;
static const int request_line_en_RFC822_Request_Line = 1;


/* #line 352 "src/network/ragel_request_line.c" */
	{
	cs = request_line_start;
	top = 0;
	}

/* #line 358 "src/network/ragel_request_line.c" */
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _request_line_trans_keys + _request_line_key_offsets[cs];
	_trans = _request_line_index_offsets[cs];

	_klen = _request_line_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _request_line_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _request_line_indicies[_trans];
	cs = _request_line_trans_targs[_trans];

	if ( _request_line_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _request_line_actions + _request_line_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
/* #line 15 "src/network/rfc822proto-statemachine.rl" */
	{ protocol_code = RFC822_Protocol_RTSP10; }
	break;
	case 1:
/* #line 17 "src/network/rfc822proto-statemachine.rl" */
	{ protocol_code = RFC822_Protocol_RTSP_UnsupportedVersion; }
	break;
	case 2:
/* #line 22 "src/network/rfc822proto-statemachine.rl" */
	{ protocol_code = RFC822_Protocol_HTTP10; }
	break;
	case 3:
/* #line 24 "src/network/rfc822proto-statemachine.rl" */
	{ protocol_code = RFC822_Protocol_HTTP11; }
	break;
	case 4:
/* #line 26 "src/network/rfc822proto-statemachine.rl" */
	{ protocol_code = RFC822_Protocol_HTTP_UnsupportedVersion; }
	break;
	case 5:
/* #line 37 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = RTSP_Method__Unsupported; }
	break;
	case 6:
/* #line 38 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = RTSP_Method_DESCRIBE; }
	break;
	case 7:
/* #line 39 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = RTSP_Method_OPTIONS; }
	break;
	case 8:
/* #line 40 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = RTSP_Method_PAUSE; }
	break;
	case 9:
/* #line 41 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = RTSP_Method_PLAY; }
	break;
	case 10:
/* #line 42 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = RTSP_Method_SETUP; }
	break;
	case 11:
/* #line 43 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = RTSP_Method_TEARDOWN; }
	break;
	case 12:
/* #line 72 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = HTTP_Method__Unsupported; }
	break;
	case 13:
/* #line 73 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = HTTP_Method_GET; }
	break;
	case 14:
/* #line 74 "src/network/rfc822proto-statemachine.rl" */
	{ method_code = HTTP_Method_POST; }
	break;
	case 15:
/* #line 10 "src/network/rfc822proto-requestline.rl" */
	{
        s = p;
    }
	break;
	case 16:
/* #line 14 "src/network/rfc822proto-requestline.rl" */
	{
        method_str = s;
        method_len = p-s;
    }
	break;
	case 17:
/* #line 19 "src/network/rfc822proto-requestline.rl" */
	{
        protocol_str = s;
        protocol_len = p-s;
    }
	break;
	case 18:
/* #line 24 "src/network/rfc822proto-requestline.rl" */
	{
        object_str = s;
        object_len = p-s;
    }
	break;
	case 19:
/* #line 29 "src/network/rfc822proto-requestline.rl" */
	{ p = pp; {cs = stack[--top]; goto _again;} }
	break;
	case 20:
/* #line 31 "src/network/rfc822proto-requestline.rl" */
	{ p = pp; {cs = stack[--top]; goto _again;} }
	break;
	case 21:
/* #line 35 "src/network/rfc822proto-requestline.rl" */
	{ method_code = 1; }
	break;
	case 22:
/* #line 37 "src/network/rfc822proto-requestline.rl" */
	{ protocol_code = RFC822_Protocol_Unsupported; }
	break;
	case 23:
/* #line 38 "src/network/rfc822proto-requestline.rl" */
	{ pp = p; p = method_str-1; {stack[top++] = cs; cs = 35; goto _again;} }
	break;
	case 24:
/* #line 39 "src/network/rfc822proto-requestline.rl" */
	{ pp = p; p = method_str-1; {stack[top++] = cs; cs = 73; goto _again;} }
	break;
/* #line 541 "src/network/ragel_request_line.c" */
		}
	}

_again:
	_acts = _request_line_actions + _request_line_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 25:
/* #line 40 "src/network/rfc822proto-requestline.rl" */
	{ {p++; goto _out; } }
	break;
/* #line 554 "src/network/ragel_request_line.c" */
		}
	}

	if ( cs == 0 )
		goto _out;
	p += 1;
	goto _resume;
	_out: {}
	}

/* #line 49 "src/network/ragel_request_line.rl" */


    if ( cs < request_line_first_final )
        return ( p == pe ) ? 0 : -1;

    /* Only set these when the parsing was successful: an incomplete
     * request line won't help!
     */
    req->proto = protocol_code;
    req->method_id = method_code;
    req->method_str = g_strndup(method_str, method_len);
    req->protocol_str = g_strndup(protocol_str, protocol_len);
    req->object = g_strndup(object_str, object_len);

    return p-msg;
}

int ragel_read_rtsp_headers(GHashTable *headers, const char *msg,
                            size_t length, size_t *read_size)
{
    return 1;
}
int ragel_read_http_headers(GHashTable *headers, const char *msg,
                            size_t length, size_t *read_size)
{
    return 1;
}

