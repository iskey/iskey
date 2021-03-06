/**
 * Copyright (c) 2004, Jan Kneschke, incremental
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the 'incremental' nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <errno.h>
#include <assert.h>

#include "conf/array.h"
#include "conf/buffer.h"

array *array_init(void) {
    array *a;

    a = calloc(1, sizeof(*a));
    assert(a);

    a->next_power_of_2 = 1;

    return a;
}

array *array_init_array(array *src) {
    size_t i;
    array *a = array_init();

    a->used = src->used;
    a->size = src->size;
    a->next_power_of_2 = src->next_power_of_2;
    a->unique_ndx = src->unique_ndx;

    a->data = malloc(sizeof(*src->data) * src->size);
    for (i = 0; i < src->size; i++) {
        if (src->data[i]) a->data[i] = src->data[i]->copy(src->data[i]);
        else a->data[i] = NULL;
    }

    a->sorted = malloc(sizeof(*src->sorted)   * src->size);
    memcpy(a->sorted, src->sorted, sizeof(*src->sorted)   * src->size);
    return a;
}

void array_free(array *a) {
    size_t i;
    if (!a) return;

    if (!a->is_weakref) {
        for (i = 0; i < a->size; i++) {
            if (a->data[i]) a->data[i]->free(a->data[i]);
        }
    }

    if (a->data) free(a->data);
    if (a->sorted) free(a->sorted);

    free(a);
}

void array_reset(array *a) {
    size_t i;
    if (!a) return;

    if (!a->is_weakref) {
        for (i = 0; i < a->used; i++) {
            a->data[i]->reset(a->data[i]);
        }
    }

    a->used = 0;
}

data_unset *array_pop(array *a) {
    data_unset *du;

    assert(a->used != 0);

    a->used --;
    du = a->data[a->used];
    a->data[a->used] = NULL;

    return du;
}

static int array_get_index(array *a, const char *key, size_t keylen, int *rndx) {
    int ndx = -1;
    int i, pos = 0;

    if (key == NULL) return -1;

    /* try to find the string */
    for (i = pos = a->next_power_of_2 / 2; ; i >>= 1) {
        int cmp;

        if (pos < 0) {
            pos += i;
        } else if (pos >= (int)a->used) {
            pos -= i;
        } else {
            cmp = buffer_caseless_compare(key, keylen, a->data[a->sorted[pos]]->key->ptr, a->data[a->sorted[pos]]->key->used);

            if (cmp == 0) {
                /* found */
                ndx = a->sorted[pos];
                break;
            } else if (cmp < 0) {
                pos -= i;
            } else {
                pos += i;
            }
        }
        if (i == 0) break;
    }

    if (rndx) *rndx = pos;

    return ndx;
}

data_unset *array_get_element(array *a, const char *key) {
    int ndx;

    if (-1 != (ndx = array_get_index(a, key, strlen(key) + 1, NULL))) {
        /* found, leave here */

        return a->data[ndx];
    }

    return NULL;
}

/* replace or insert data, return the old one with the same key */
data_unset *array_replace(array *a, data_unset *du) {
    int ndx;

    if (-1 == (ndx = array_get_index(a, du->key->ptr, du->key->used, NULL))) {
        array_insert_unique(a, du);
        return NULL;
    } else {
        data_unset *old = a->data[ndx];
        a->data[ndx] = du;
        return old;
    }
}

int array_insert_unique(array *a, data_unset *str) {
    int ndx = -1;
    int pos = 0;
    size_t j;

    /* generate unique index if neccesary */
    if (str->key->used == 0 || str->is_index_key) {
        buffer_copy_long(str->key, a->unique_ndx++);
        str->is_index_key = 1;
    }

    /* try to find the string */
    if (-1 != (ndx = array_get_index(a, str->key->ptr, str->key->used, &pos))) {
        /* found, leave here */
        if (a->data[ndx]->type == str->type) {
            str->insert_dup(a->data[ndx], str);
        } else {
            fprintf(stderr, "a\n");
        }
        return 0;
    }

    /* insert */

    if (a->used+1 > INT_MAX) {
        /* we can't handle more then INT_MAX entries: see array_get_index() */
        return -1;
    }

    if (a->size == 0) {
        a->size   = 16;
        a->data   = malloc(sizeof(*a->data)     * a->size);
        a->sorted = malloc(sizeof(*a->sorted)   * a->size);
        assert(a->data);
        assert(a->sorted);
        for (j = a->used; j < a->size; j++) a->data[j] = NULL;
    } else if (a->size == a->used) {
        a->size  += 16;
        a->data   = realloc(a->data,   sizeof(*a->data)   * a->size);
        a->sorted = realloc(a->sorted, sizeof(*a->sorted) * a->size);
        assert(a->data);
        assert(a->sorted);
        for (j = a->used; j < a->size; j++) a->data[j] = NULL;
    }

    ndx = (int) a->used;

    a->data[a->used++] = str;

    if (pos != ndx &&
        ((pos < 0) ||
         buffer_caseless_compare(str->key->ptr, str->key->used, a->data[a->sorted[pos]]->key->ptr, a->data[a->sorted[pos]]->key->used) > 0)) {
        pos++;
    }

    /* move everything on step to the right */
    if (pos != ndx) {
        memmove(a->sorted + (pos + 1), a->sorted + (pos), (ndx - pos) * sizeof(*a->sorted));
    }

    /* insert */
    a->sorted[pos] = ndx;

    if (a->next_power_of_2 == (size_t)ndx) a->next_power_of_2 <<= 1;

    return 0;
}

void array_print_indent(int depth) {
    int i;
    for (i = 0; i < depth; i ++) {
        fprintf(stdout, "    ");
    }
}

size_t array_get_max_key_length(array *a) {
    size_t maxlen, i;

    maxlen = 0;
    for (i = 0; i < a->used; i ++) {
        data_unset *du = a->data[i];
        size_t len = strlen(du->key->ptr);

        if (len > maxlen) {
            maxlen = len;
        }
    }
    return maxlen;
}

int array_print(array *a, int depth) {
    size_t i;
    size_t maxlen;
    int oneline = 1;

    if (a->used > 5) {
        oneline = 0;
    }
    for (i = 0; i < a->used && oneline; i++) {
        data_unset *du = a->data[i];
        if (!du->is_index_key) {
            oneline = 0;
            break;
        }
        switch (du->type) {
            case TYPE_INTEGER:
            case TYPE_STRING:
            case TYPE_COUNT:
                break;
            default:
                oneline = 0;
                break;
        }
    }
    if (oneline) {
        fprintf(stdout, "(");
        for (i = 0; i < a->used; i++) {
            data_unset *du = a->data[i];
            if (i != 0) {
                fprintf(stdout, ", ");
            }
            du->print(du, depth + 1);
        }
        fprintf(stdout, ")");
        return 0;
    }

    maxlen = array_get_max_key_length(a);
    fprintf(stdout, "(\n");
    for (i = 0; i < a->used; i++) {
        data_unset *du = a->data[i];
        array_print_indent(depth + 1);
        if (!du->is_index_key) {
            int j;

            if (i && (i % 5) == 0) {
                fprintf(stdout, "# %zd\n", i);
                array_print_indent(depth + 1);
            }
            fprintf(stdout, "\"%s\"", du->key->ptr);
            for (j = maxlen - strlen(du->key->ptr); j > 0; j --) {
                fprintf(stdout, " ");
            }
            fprintf(stdout, " => ");
        }
        du->print(du, depth + 1);
        fprintf(stdout, ",\n");
    }
    if (!(i && (i - 1 % 5) == 0)) {
        array_print_indent(depth + 1);
        fprintf(stdout, "# %zd\n", i);
    }
    array_print_indent(depth);
    fprintf(stdout, ")");

    return 0;
}

#ifdef DEBUG_ARRAY

#include "data_count.c"

int main (int argc, char **argv) {
    array *a;
    data_string *ds;
    data_count *dc;

    UNUSED(argc);
    UNUSED(argv);

    a = array_init();

    ds = data_string_init();
    buffer_copy_string(ds->key, "abc");
    buffer_copy_string(ds->value, "alfrag");

    array_insert_unique(a, (data_unset *)ds);

    ds = data_string_init();
    buffer_copy_string(ds->key, "abc");
    buffer_copy_string(ds->value, "hameplman");

    array_insert_unique(a, (data_unset *)ds);

    ds = data_string_init();
    buffer_copy_string(ds->key, "123");
    buffer_copy_string(ds->value, "alfrag");

    array_insert_unique(a, (data_unset *)ds);

    dc = data_count_init();
    buffer_copy_string(dc->key, "def");

    array_insert_unique(a, (data_unset *)dc);

    dc = data_count_init();
    buffer_copy_string(dc->key, "def");

    array_insert_unique(a, (data_unset *)dc);

    array_print(a, 0);

    array_free(a);

    fprintf(stderr, "%d\n",
           buffer_caseless_compare(CONST_STR_LEN("Content-Type"), CONST_STR_LEN("Content-type")));

    return 0;
}
#endif
