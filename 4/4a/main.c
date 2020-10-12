#include "util.h"

#define SYS_WRITE 4
#define STDOUT 1
#define O_DIRECTORY        00200000  
#define O_RDONLY        00000000
/*extern int system_call(int a, int b,char* c,int d);
*/
         struct linux_dirent {
              unsigned long  d_ino;     /* Inode number */
              unsigned long  d_off;     /* Offset to next linux_dirent */
               unsigned short d_reclen;  /* Length of this linux_dirent */
                 char           d_name[1];  /* Filename (null-terminated) */
                            /* length is actually (d_reclen - 2 -
	       *                                     offsetof(struct linux_dirent, d_name)) */
	                    
			             /*   char           pad;   */    /* Zero padding byte*/
		                        /*       char           d_type;*/    /* File type (only since Linux*/
		                                                                           /* 2.6.4); offset is (d_reclen - 1)*/
              };



int main (int argc , char* argv[], char*nenvp[])
{
  int i,fd,nread;
  char buf[2000];
  struct linux_dirent *d,d1;
  int bpos;
  char d_type;
  char * str;
  fd=-1;
  fd=system_call(5,".",0| 00200000,00777);
 char* s1 = itoa(fd);
                      system_call(SYS_WRITE,STDOUT,s1,strlen(s1));
  nread=system_call(217, fd,buf, 2000);
    
 char* s = itoa(nread);
                     system_call(SYS_WRITE,STDOUT,s,strlen(s));

/*   if (nread == -1)
	              break;

           if (nread == 0)
		               break;
*/		   
		     for (bpos = 0; bpos < nread;) {
         d = (struct linux_dirent *) (buf + bpos);
 
              d_type = *(buf + bpos + d->d_reclen - 1);
               char* t= (d_type == 8) ?  "regular" :
              (d_type == 4) ?  "directory" :
                  (d_type ==1) ? "FIFO" :
             (d_type ==12) ? "socket" :
               (d_type ==10) ?  "symlink" :
              (d_type ==6) ?  "block dev" :
               (d_type ==2) ?  "char dev" : "???";
              unsigned short l= d->d_reclen;
             char* n= (char *) d->d_name;
  system_call(SYS_WRITE,STDOUT,"length ", 8);
            str = itoa((int)l);
	          system_call(SYS_WRITE,STDOUT,str,strlen(str));
		        system_call(SYS_WRITE,STDOUT," name",6);
			      system_call(SYS_WRITE,STDOUT,n,strlen(n));
                    system_call(SYS_WRITE,STDOUT," type",6);
		                                  system_call(SYS_WRITE,STDOUT,t,strlen(t));
			      system_call(SYS_WRITE,STDOUT,"\n",1);

               bpos += d->d_reclen;
 }
 /* str = itoa(argc);
  system_call(SYS_WRITE,STDOUT, str,strlen(str));
  system_call(SYS_WRITE,STDOUT," arguments \n", 12);
  for (i = 0 ; i < argc ; i++)
    {
      system_call(SYS_WRITE,STDOUT,"argv[", 5);
	  str = itoa(i);
      system_call(SYS_WRITE,STDOUT,str,strlen(str));
      system_call(SYS_WRITE,STDOUT,"] = ",4);
      system_call(SYS_WRITE,STDOUT,argv[i],strlen(argv[i]));
      system_call(SYS_WRITE,STDOUT,"\n",1);
    }*/
   system_call(6,fd);
  return 0;
}
