/**
 * @file
 * Config/command parsing
 *
 * @authors
 * Copyright (C) 1996-2002,2007,2010,2012-2013,2016 Michael R. Elkins <me@mutt.org>
 * Copyright (C) 2004 g10 Code GmbH
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MUTT_INIT_H
#define MUTT_INIT_H

#include <stddef.h>
#include <stdbool.h>
#include "core/lib.h"
#include "mutt.h"
#include "hook.h"

struct Buffer;
struct ConfigSet;
struct ListHead;

void                  init_config            (struct ConfigSet *cs);
int                   mutt_command_complete  (char *buf, size_t buflen, int pos, int numtabs);
int                   mutt_extract_token     (struct Buffer *dest, struct Buffer *tok, TokenFlags flags);
HookFlags             mutt_get_hook_type     (const char *name);
int                   mutt_init              (struct ConfigSet *cs, bool skip_sys_rc, struct ListHead *commands);
int                   mutt_label_complete    (char *buf, size_t buflen, int numtabs);
bool                  mutt_nm_query_complete (char *buf, size_t buflen, int pos, int numtabs);
bool                  mutt_nm_tag_complete   (char *buf, size_t buflen, int numtabs);
void                  mutt_opts_free         (void);
enum CommandResult    mutt_parse_rc_buffer   (struct Buffer *line, struct Buffer *token, struct Buffer *err);
enum CommandResult    mutt_parse_rc_line     (const char *line, struct Buffer *err);
int                   mutt_query_variables   (struct ListHead *queries, bool show_docs);
int                   mutt_var_value_complete(char *buf, size_t buflen, int pos);

#endif /* MUTT_INIT_H */
