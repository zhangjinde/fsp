    /*********************************************************************\
    *  Copyright (c) 1991 by Wen-King Su (wen-king@vlsi.cs.caltech.edu)   *
    *                                                                     *
    *  You may copy or modify this file in any manner you wish, provided  *
    *  that this notice is always included, and that you hold the author  *
    *  harmless for any loss or damage resulting from the installation or *
    *  use of this software.                                              *
    \*********************************************************************/

#include "tweak.h"
#include "client_def.h"
#include "c_extern.h"
#include "bsd_extern.h"
#ifdef STDC_HEADERS
#include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include "my-string.h"

static int remove_it PROTO1(char *, p)
{
  char *op;
  UBUF *ub;
  
  op = util_abs_path(p);
  
  ub = client_interact(CC_DEL_FILE,0L, strlen(op), (unsigned char *)op+1, 0,
		       (unsigned char *)NULLP);
  
  if(ub->cmd == CC_ERR) {
    fprintf(stderr,"Can't remove %s: %s\n",p,ub->buf);
    free(op); return(-1);
  }
  return(0);
}

int main PROTO2(int, argc, char **, argv)
{
  char **av, *av2[2];
  
  env_client();
  
  while(*++argv) {
    if(!(av = glob(*argv))) {
      av = av2;
      av2[0] = *argv;
      av2[1] = 0;
    }
    while(*av) remove_it(*av++);
  }
  
  client_done();
  
  exit(0);
}