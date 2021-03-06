/*******************************************************************************
 *
 *                              Delta Chat Core
 *                      Copyright (C) 2017 Björn Petersen
 *                   Contact: r10s@b44t.com, http://b44t.com
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see http://www.gnu.org/licenses/ .
 *
 ******************************************************************************/


#ifndef __MRAPEERSTATE_H__
#define __MRAPEERSTATE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "mrkey.h"


typedef struct mraheader_t mraheader_t;


#define MRA_PE_NOPREFERENCE   0 /* prefer-encrypt states */
#define MRA_PE_MUTUAL         1
#define MRA_PE_GOSSIP         2
#define MRA_PE_RESET         20


/**
 * Library-internal.
 */
typedef struct mrapeerstate_t
{
	/** @privatesection */
	char*          m_addr;
	time_t         m_last_seen;
	time_t         m_last_seen_autocrypt;
	mrkey_t*       m_public_key; /*!=NULL*/
	int            m_prefer_encrypt;

	#define        MRA_SAVE_LAST_SEEN 0x01
	#define        MRA_SAVE_ALL       0x02
	int            m_to_save;
} mrapeerstate_t;


mrapeerstate_t* mrapeerstate_new             (); /* the returned pointer is ref'd and must be unref'd after usage */
void            mrapeerstate_unref           (mrapeerstate_t*);

int             mrapeerstate_init_from_header  (mrapeerstate_t*, const mraheader_t*, time_t message_time);
int             mrapeerstate_degrade_encryption(mrapeerstate_t*, time_t message_time);
int             mrapeerstate_apply_header      (mrapeerstate_t*, const mraheader_t*, time_t message_time); /*returns 1 on changes*/

int             mrapeerstate_load_from_db__  (mrapeerstate_t*, mrsqlite3_t*, const char* addr);
int             mrapeerstate_save_to_db__    (const mrapeerstate_t*, mrsqlite3_t*, int create);


#ifdef __cplusplus
} /* /extern "C" */
#endif
#endif /* __MRAPEERSTATE_H__ */

