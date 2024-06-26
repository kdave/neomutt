/**
 * @file
 * The "currently-open" mailbox
 *
 * @authors
 * Copyright (C) 2017 Richard Russon <rich@flatcap.org>
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

#ifndef MUTT_CONTEXT_H
#define MUTT_CONTEXT_H

#include <stdbool.h>
#include <sys/types.h>

struct Email;
struct EmailList;
struct Mailbox;
struct NotifyCallback;

/**
 * struct Context - The "current" mailbox
 */
struct Context
{
  off_t vsize;                       ///< Size (in bytes) of the messages shown
  char *pattern;                     ///< Limit pattern string
  struct PatternList *limit_pattern; ///< Compiled limit pattern
  struct ThreadsContext *threads;    ///< Threads context
  int msg_in_pager;                  ///< Message currently shown in the pager

  struct Menu *menu;                 ///< Needed for pattern compilation

  bool collapsed : 1;                ///< Are all threads collapsed?

  struct Mailbox *mailbox;           ///< Current Mailbox
  struct Notify *notify;             ///< Notifications: #NotifyContext, #EventContext
};

/**
 * enum NotifyContext - Types of Context Event
 *
 * Observers of #NT_CONTEXT will be passed an #EventContext.
 */
enum NotifyContext
{
  NT_CONTEXT_ADD = 1, ///< The Context has been opened
  NT_CONTEXT_DELETE,  ///< The Context is about to be destroyed
  NT_CONTEXT_CHANGE,  ///< The Context has changed
};

/**
 * struct EventContext - An Event that happened to an Context
 */
struct EventContext
{
  struct Context *ctx; ///< The Context this Event relates to
};

void            ctx_free            (struct Context **ptr);
int             ctx_mailbox_observer(struct NotifyCallback *nc);
struct Context *ctx_new             (struct Mailbox *m);
void            ctx_update          (struct Context *ctx);
bool            ctx_has_limit       (const struct Context *ctx);
struct Mailbox* ctx_mailbox         (struct Context *ctx);

bool message_is_tagged(struct Email *e);
struct Email *mutt_get_virt_email(struct Mailbox *m, int vnum);

int  el_add_tagged  (struct EmailList *el, struct Context *ctx, struct Email *e, bool use_tagged);

#endif /* MUTT_CONTEXT_H */
