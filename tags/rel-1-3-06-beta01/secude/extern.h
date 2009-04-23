/* extern.h - The collection of external definitions needed. */

/*  This file is part of GDBM, the GNU data base manager, by Philip A. Nelson.
    Copyright (C) 1990, 1991  Free Software Foundation, Inc.

    GDBM is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 1, or (at your option)
    any later version.

    GDBM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDBM; see the file COPYING.  If not, write to
    the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

    You may contact the author by:
       e-mail:  phil@cs.wwu.edu
      us-mail:  Philip A. Nelson
                Computer Science Department
                Western Washington University
                Bellingham, WA 98226
        phone:  (206) 676-3035
       
*************************************************************************/


/* The global variables used for the "original" interface. */
extern gdbm_file_info  *_gdbm_file;

/* Memory for return data for the "original" interface. */
extern datum _gdbm_memory;
extern char *_gdbm_fetch_val;


/* External routines used. */

extern gdbm_file_info * SEC_API_CALLING_CONV gdbm_open ();

extern datum SEC_API_CALLING_CONV gdbm_fetch ();

extern datum SEC_API_CALLING_CONV gdbm_firstkey ();

extern datum SEC_API_CALLING_CONV gdbm_nextkey ();

extern int SEC_API_CALLING_CONV gdbm_delete ();

extern int SEC_API_CALLING_CONV gdbm_store ();

extern void SEC_API_CALLING_CONV gdbm_close ();
