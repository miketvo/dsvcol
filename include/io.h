//
// Created by miketvo on 6/1/2022.
//

#ifndef DSVCOL_IO_H
#define DSVCOL_IO_H

#include <stdio.h>


/***
 * <p><strong>getline()</strong> was originally GNU extensions. It was standardized in POSIX.1-2008.
 * This is a portable implementation written specifically for dsvcol.</p>
 *
 *
 * <h1>POSIX Specifications</h1>
 * <p>As found on:
 * <a href="https://man7.org/linux/man-pages/man3/getline.3.html">
 * https://man7.org/linux/man-pages/man3/getline.3.html
 * </a></p>
 *
 *
 * <h2>Synopsis</h2>
 *
 * <pre>
 *     #include &lt;stdio.h&gt;
 * </pre>
 * <pre>
 *     ssize_t getline(char **restrict lineptr, size_t *restrict n,
 *                     FILE *restrict stream);
 * </pre>
 *
 *
 * <h2>Description</h2>
 *
 * <p><strong>getline()</strong> reads an entire line from stream, storing the address
 * of the buffer containing the text into *lineptr. The buffer is
 * null-terminated and includes the newline character, if one was
 * found.</p>
 *
 * <p>If *lineptr is set to NULL before the call, then <strong>getline()</strong> will
 * allocate a buffer for storing the line. This buffer should be
 * freed by the user program even if <strong>getline()</strong> failed.</p>
 *
 * <p>Alternatively, before calling <strong>getline()</strong>, *lineptr can contain a
 * pointer to a <i>malloc()</i>-allocated buffer *n bytes in size. If the
 * buffer is not large enough to hold the line, <strong>getline()</strong> resizes it
 * with <i>realloc()</i>, updating *lineptr and *n as necessary.</p>
 *
 * <p>In either case, on a successful call, *lineptr and *n will be
 * updated to reflect the buffer address and allocated size
 * respectively.</p>
 *
 *
 * <h2>Errors</h2>
 *
 * <ul>
 *     <li><strong>EINVAL</strong> Bad arguments (n or lineptr is NULL, or stream is not valid).</li>
 *     <li><strong>ENOMEM</strong> Allocation or reallocation of the line buffer failed.</li>
 * </ul>
 *
 * @param lineptr
 * @param n
 * @param stream
 * @return <p>On success, <strong>getline()</strong> return the number of
 * characters read, including the delimiter character, but not
 * including the terminating null byte ('\0').  This value can be
 * used to handle embedded null bytes in the line read.</p>
 * <p><strong>getline()</strong> returns -1 on failure to read a line (including
 * end-of-file condition).  In the event of a failure, <i>errno</i> is set
 * to indicate the error.</p>
 */
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

#endif //DSVCOL_IO_H
