

/* Abort with an error message.  */
void
__libc_message (int do_abort, const char *fmt, ...)
{

}

void
__libc_fatal (message)
     const char *message;
{
  /* The loop is added only to keep gcc happy.  */
  while (1)
    __libc_message (1, "%s", message);
}
libc_hidden_def (__libc_fatal)
