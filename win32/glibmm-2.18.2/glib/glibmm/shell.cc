// Generated by gtkmmproc -- DO NOT MODIFY!


#include <glibmm/shell.h>
#include <glibmm/private/shell_p.h>

// -*- c++ -*-
/* $Id: shell.ccg,v 1.1 2003/01/07 16:58:38 murrayc Exp $ */

/* Copyright (C) 2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <glibmm/utility.h>


namespace Glib
{

/**** shell utility functions **********************************************/

Glib::ArrayHandle<std::string> shell_parse_argv(const std::string& command_line)
{
  char**  argv  = 0;
  int     argc  = 0;
  GError* error = 0;

  g_shell_parse_argv(command_line.c_str(), &argc, &argv, &error);

  if(error)
    Glib::Error::throw_exception(error);

  return Glib::ArrayHandle<std::string>(argv, argc, Glib::OWNERSHIP_DEEP);
}

std::string shell_quote(const std::string& unquoted_string)
{
  const ScopedPtr<char> buf (g_shell_quote(unquoted_string.c_str()));
  return std::string(buf.get());
}

std::string shell_unquote(const std::string& quoted_string)
{
  GError* error = 0;
  char *const buf = g_shell_unquote(quoted_string.c_str(), &error);

  if(error)
    Glib::Error::throw_exception(error);

  return std::string(ScopedPtr<char>(buf).get());
}

} // namespace Glib


namespace
{
} // anonymous namespace


Glib::ShellError::ShellError(Glib::ShellError::Code error_code, const Glib::ustring& error_message)
:
  Glib::Error (G_SHELL_ERROR, error_code, error_message)
{}

Glib::ShellError::ShellError(GError* gobject)
:
  Glib::Error (gobject)
{}

Glib::ShellError::Code Glib::ShellError::code() const
{
  return static_cast<Code>(Glib::Error::code());
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
void Glib::ShellError::throw_func(GError* gobject)
{
  throw Glib::ShellError(gobject);
}
#else
//When not using exceptions, we just pass the Exception object around without throwing it:
std::auto_ptr<Glib::Error> Glib::ShellError::throw_func(GError* gobject)
{
  return std::auto_ptr<Glib::Error>(new Glib::ShellError(gobject));
}
#endif //GLIBMM_EXCEPTIONS_ENABLED

