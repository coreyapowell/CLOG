/*  CLOG.h -
 MIT License

Copyright (c) 2025 Corey Adam Powell

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*  CLOG is intended to be redefined per the programmer's purposes. In fact, there should be an 
    accompanied unclog program that removes any of these macros and strips the code of any mention.
    flags can be moved around, changed, or appended on a moment's notice. So there truly is no 
    protection on the use of these macros. What is preserved is the meaning and use of the terms.

    Design Principles: 
    - CLOGGING: flag that may turn on or off code if a developer needs to refrain from emitting code
      #include "CLOG.h" a second time will nullify or activate the macros based on this flag.
    - CLOGGER - the FILE for CLOGGING. This defaults to stderr, but a program or module can immediately
      redefine this. When it is NULL, there's no CLOGGER, and there's no CLOGGING. This allows linked
      modules to synchronize their CLOGGERS for synchronous CLOGGING. This is a standard, and seeing a
      CLOGGER in a module indicates to another programmer that synchronized CLOGGING is available.
      It also makes CLOGGING controllable on a module level if CLOGGING is enabled at compile time
      for that body or section of code.
    - CLOG(__VA_ARGS) - normally passes forward to fprintf, but this is is intended to be redefined.

    These three names can be reused as needed, but the design principles remain the same.
    1) CLOG can be redefined for any code you need!
    2) CLOGGING can be used in your code to trigger anything you want!
    3) CLOGGER can be reconfigured as needed as a stream, file, handle, or buffer type of object.
    - it would be preferrable to maintain the standard or document the essential nature of CLOGGER

    The same principles, three by three, can hiterthere to their application be:
    CLOG, CLOGGER, CLOGGING - calling code by name or just documenting calls by name
    FLOG, FLOGGER, FLOGGING - logging functional steps and values (or as needed repetitiously )
    BLOG, BLOGGER, BLOGGING - documentation of what's going on or how things work

    CLOGKAWT - either the standard system line terminator or any line terminator you may need.
    STRANG - this is the text passed through VA_ARGS to fprintf. this should always be preserved!

      All I ask is that you maintain the naming conventions and try not to laugh when you're writing code.
      if you have suggestions or would like to expand the use of these terms, feel free to contact me.

*/

#ifndef CLOG_MACROS
#define CLOG_MACROS

#ifndef CLOGGER
#define CLOGGER stderr
#endif

#define CLOGKAWT "\r\n"
#define CLOGGING 1
#define FLOGGING 1
#define BLOGGING 1

#else
#undef CLOG
#undef FLOG
#undef TLOG
#endif // CLOG_MACROS

#if defined(CLOGGING) && (CLOGGING == 1)

#define CLOG(STRANG,...)  if((CLOGGING != 0) { if (CLOGGER != 0)) {\
    fprintf(CLOGGER,STRANG CLOGKAWT, __VA_ARGS__); } }
#else
#define CLOG(...) {}

#endif // CLOGGING

#if defined(FLOGGING) && (FLOGGING == 1)
#define FLOG(STRANG,...) if((FLOGGING != 0) { if (FLOGGER != 0)) {\
    fprintf(FLOGGER," [%d] " STRANG CLOGKAWT,__LINE__,__VA_ARGS__); } }
#else
#define FLOG(...) {}
#endif // FLOGGING

#if defined(BLOGGING) && (BLOGGING == 1)
#define FLOG(STRANG,...) if((BLOGGING != 0) { if (BLOGGER != 0)) {\
    fprintf(BLOGGER," [%d] " STRANG CLOGKAWT,__LINE__,__VA_ARGS__); } }
#else
#define FLOG(...) {}

#endif // BLOGGING
