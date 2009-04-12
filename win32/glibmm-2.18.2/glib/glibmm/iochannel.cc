// Generated by gtkmmproc -- DO NOT MODIFY!


#include <glibmm/iochannel.h>
#include <glibmm/private/iochannel_p.h>

// -*- c++ -*-
/* $Id: iochannel.ccg,v 1.6 2006/10/04 12:04:09 murrayc Exp $ */

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

#include <glibmm/exceptionhandler.h>
#include <glibmm/iochannel.h>
#include <glibmm/utility.h>
#include <glibmm/main.h>


namespace
{

// Glib::IOChannel reference counting issues:
//
// Normally, you'd expect that the C++ object stays around as long as the
// C instance does.  Also Glib::wrap() usually returns always the same C++
// wrapper object for a single C instance.
//
// Unfortunately it isn't possible to implement these features if we didn't
// create the underlying GIOChannel.  That is, when wrapping existing
// GIOChannel instances such as returned by e.g. g_io_channel_unix_new() or
// g_io_channel_new_file().  Neither is there a way to hook up a wrapper
// object in an existing GIOChannel, nor exists any destroy notification.
//
// So that means:  If the IOChannel is implemented in C++ -- that is, our
// GlibmmIOChannel backend is used -- we use the GIOChannel reference
// counting mechanism.  If the IOChannel backend is unknown, then the
// wrapper instance holds always exactly one reference to the GIOChannel.
// The wrapper object itself is then managed via our own refcounting
// mechanism.  To do that a utility class ForeignIOChannel is introduced to
// override reference() and unreference().

class ForeignIOChannel : public Glib::IOChannel
{
public:
  ForeignIOChannel(GIOChannel* gobject, bool take_copy)
    : Glib::IOChannel(gobject, take_copy), ref_count_(0) {}

  virtual void reference()   const;
  virtual void unreference() const;

private:
  mutable int ref_count_;
};

void ForeignIOChannel::reference() const
{
  ++ref_count_;
}

void ForeignIOChannel::unreference() const
{
  if (!(--ref_count_)) delete this;
}

} // anonymous namespace


namespace Glib
{

class GlibmmIOChannel
{
public:
  GIOChannel        base;
  Glib::IOChannel*  wrapper;

  static const GIOFuncs vfunc_table;

  static GIOStatus io_read(GIOChannel* channel, char* buf, gsize count,
                           gsize* bytes_read, GError** err);

  static GIOStatus io_write(GIOChannel* channel, const char* buf, gsize count,
                            gsize* bytes_written, GError** err);

  static GIOStatus io_seek (GIOChannel* channel, gint64 offset, GSeekType type, GError** err);
  static GIOStatus io_close(GIOChannel* channel, GError** err);

  static GSource*  io_create_watch(GIOChannel* channel, GIOCondition condition);
  static void      io_free(GIOChannel* channel);

  static GIOStatus io_set_flags(GIOChannel* channel, GIOFlags flags, GError** err);
  static GIOFlags  io_get_flags(GIOChannel* channel);
};

// static
const GIOFuncs GlibmmIOChannel::vfunc_table =
{
  &GlibmmIOChannel::io_read,
  &GlibmmIOChannel::io_write,
  &GlibmmIOChannel::io_seek,
  &GlibmmIOChannel::io_close,
  &GlibmmIOChannel::io_create_watch,
  &GlibmmIOChannel::io_free,
  &GlibmmIOChannel::io_set_flags,
  &GlibmmIOChannel::io_get_flags,
};


/**** GLib::IOChannel ******************************************************/

/* Construct a custom C++-implemented IOChannel.  GlibmmIOChannel is an
 * extended GIOChannel struct which allows us to hook up a pointer to this
 * persistent wrapper instance.
 */
IOChannel::IOChannel()
:
  gobject_ (static_cast<GIOChannel*>(g_malloc(sizeof(GlibmmIOChannel))))
{
  g_io_channel_init(gobject_);
  gobject_->funcs = const_cast<GIOFuncs*>(&GlibmmIOChannel::vfunc_table);

  reinterpret_cast<GlibmmIOChannel*>(gobject_)->wrapper = this;
}

/* Construct an IOChannel wrapper for an already created GIOChannel.
 * See the comment at the top of this file for an explanation of the
 * problems with this approach.
 */
IOChannel::IOChannel(GIOChannel* gobject, bool take_copy)
:
  gobject_ (gobject)
{
  // This ctor should never be called for GlibmmIOChannel instances.
  g_assert(gobject != 0);
  g_assert(gobject->funcs != &GlibmmIOChannel::vfunc_table);

  if(take_copy)
    g_io_channel_ref(gobject_);
}

IOChannel::~IOChannel()
{
  if(gobject_)
  {
    // Check whether this IOChannel is implemented in C++, i.e. whether it
    // uses our GlibmmIOChannel forwarding backend.  Normally, this will never
    // be true because the wrapper should only be deleted in the io_free()
    // callback, which clears gobject_ before deleting.  But in case the ctor
    // of a derived class threw an exception the GIOChannel must be destroyed
    // prematurely.
    //
    if(gobject_->funcs == &GlibmmIOChannel::vfunc_table)
    {
      // Disconnect the wrapper object so that it won't be deleted twice.
      reinterpret_cast<GlibmmIOChannel*>(gobject_)->wrapper = 0;
    }

    GIOChannel *const tmp_gobject = gobject_;
    gobject_ = 0;

    g_io_channel_unref(tmp_gobject);
  }
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
Glib::RefPtr<IOChannel> IOChannel::create_from_file(const std::string& filename, const std::string& mode)
#else
Glib::RefPtr<IOChannel> IOChannel::create_from_file(const std::string& filename, const std::string& mode, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  GIOChannel *const channel = g_io_channel_new_file(filename.c_str(), mode.c_str(), &gerror);

  if(gerror)
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    Glib::Error::throw_exception(gerror);
    #else
    error = Glib::Error::throw_exception(gerror);
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }

  return Glib::wrap(channel, false);
}

Glib::RefPtr<IOChannel> IOChannel::create_from_fd(int fd)
{
  return Glib::wrap(g_io_channel_unix_new(fd), false);
}

#ifdef G_OS_WIN32

Glib::RefPtr<IOChannel> IOChannel::create_from_win32_fd(int fd)
{
  return Glib::wrap(g_io_channel_win32_new_fd(fd), false);
}

Glib::RefPtr<IOChannel> IOChannel::create_from_win32_socket(int socket)
{
  return Glib::wrap(g_io_channel_win32_new_socket(socket), false);
}

#endif /* G_OS_WIN32 */

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::write(const Glib::ustring& str)
#else
IOStatus IOChannel::write(const Glib::ustring& str, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  gsize bytes_written = 0;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  return write(str.data(), str.bytes(), bytes_written);
#else
  return write(str.data(), str.bytes(), bytes_written, error);
#endif //GLIBMM_EXCEPTIONS_ENABLED
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::read_line(Glib::ustring& line)
#else
IOStatus IOChannel::read_line(Glib::ustring& line, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  Glib::ScopedPtr<char> buf;
  GError* gerror = 0;
  gsize   bytes = 0;

  const GIOStatus status = g_io_channel_read_line(gobj(), buf.addr(), &bytes, 0, &gerror);

  if(gerror)
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    Glib::Error::throw_exception(gerror);
    #else
    error = Glib::Error::throw_exception(gerror);
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }

  if(buf.get())
    line.assign(buf.get(), buf.get() + bytes);
  else
    line.erase();

  return (IOStatus) status;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::read_to_end(Glib::ustring& str)
#else
IOStatus IOChannel::read_to_end(Glib::ustring& str, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  Glib::ScopedPtr<char> buf;
  GError* gerror = 0;
  gsize   bytes = 0;

  const GIOStatus status = g_io_channel_read_to_end(gobj(), buf.addr(), &bytes, &gerror);

  if(gerror)
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    Glib::Error::throw_exception(gerror);
    #else
    error = Glib::Error::throw_exception(gerror);
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }

  if(buf.get())
    str.assign(buf.get(), buf.get() + bytes);
  else
    str.erase();

  return (IOStatus) status;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::read(Glib::ustring& str, gsize count)
#else
IOStatus IOChannel::read(Glib::ustring& str, gsize count, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  Glib::ScopedPtr<char> buf (g_new(char, count));
  GError* gerror = 0;
  gsize   bytes = 0;

  const GIOStatus status = g_io_channel_read_chars(gobj(), buf.get(), count, &bytes, &gerror);

 if(gerror)
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    Glib::Error::throw_exception(gerror);
    #else
    error = Glib::Error::throw_exception(gerror);
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }

  if(buf.get())
    str.assign(buf.get(), buf.get() + bytes);
  else
    str.erase();

  return (IOStatus) status;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::set_encoding(const std::string& encoding)
#else
IOStatus IOChannel::set_encoding(const std::string& encoding, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;

  const GIOStatus status = g_io_channel_set_encoding(
      gobj(), (encoding.empty()) ? 0 : encoding.c_str(), &gerror);

  if(gerror)
  {
    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    Glib::Error::throw_exception(gerror);
    #else
    error = Glib::Error::throw_exception(gerror);
    #endif //GLIBMM_EXCEPTIONS_ENABLED
  }

  return (IOStatus) status;
}

std::string IOChannel::get_encoding() const
{
  const char *const encoding = g_io_channel_get_encoding(gobject_);
  return (encoding) ? std::string(encoding) : std::string();
}

void IOChannel::set_line_term(const std::string& term)
{
  if(term.empty())
    g_io_channel_set_line_term(gobj(), 0, 0);
  else
    g_io_channel_set_line_term(gobj(), term.data(), term.size());
}

std::string IOChannel::get_line_term() const
{
  int len = 0;
  const char *const term = g_io_channel_get_line_term(gobject_, &len);

  return (term) ? std::string(term, len) : std::string();
}

Glib::RefPtr<IOSource> IOChannel::create_watch(IOCondition condition)
{
  // The corresponding unreference() takes place in the dtor
  // of the Glib::RefPtr<IOChannel> object below.
  reference();
  return IOSource::create(Glib::RefPtr<IOChannel>(this), condition);
}

IOStatus IOChannel::read_vfunc(char*, gsize, gsize&)
{
  g_assert_not_reached();
  return IO_STATUS_ERROR;
}

IOStatus IOChannel::write_vfunc(const char*, gsize, gsize&)
{
  g_assert_not_reached();
  return IO_STATUS_ERROR;
}

IOStatus IOChannel::seek_vfunc(gint64, SeekType)
{
  g_assert_not_reached();
  return IO_STATUS_ERROR;
}

IOStatus IOChannel::close_vfunc()
{
  g_assert_not_reached();
  return IO_STATUS_ERROR;
}

Glib::RefPtr<Glib::Source> IOChannel::create_watch_vfunc(IOCondition)
{
  g_assert_not_reached();
  return Glib::RefPtr<Glib::Source>();
}

IOStatus IOChannel::set_flags_vfunc(IOFlags)
{
  g_assert_not_reached();
  return IO_STATUS_ERROR;
}

IOFlags IOChannel::get_flags_vfunc()
{
  g_assert_not_reached();
  return IOFlags(0);
}

void IOChannel::reference() const
{
  g_io_channel_ref(gobject_);
}

void IOChannel::unreference() const
{
  g_io_channel_unref(gobject_);
}

Glib::RefPtr<IOChannel> wrap(GIOChannel* gobject, bool take_copy)
{
  IOChannel* cpp_object = 0;

  if(gobject)
  {
    if(gobject->funcs == &GlibmmIOChannel::vfunc_table)
    {
      cpp_object = reinterpret_cast<GlibmmIOChannel*>(gobject)->wrapper;

      if(take_copy && cpp_object)
        cpp_object->reference();
    }
    else
    {
      cpp_object = new ForeignIOChannel(gobject, take_copy);
      cpp_object->reference(); // the refcount is initially 0
    }
  }

  return Glib::RefPtr<IOChannel>(cpp_object);
}


/**** Glib::GlibmmIOChannel ************************************************/

#ifdef GLIBMM_EXCEPTIONS_ENABLED
GIOStatus GlibmmIOChannel::io_read(GIOChannel* channel, char* buf, gsize count,
                                   gsize* bytes_read, GError** err)
#else
//Avoid an unused parameter warning when GLIBMM_EXCEPTIONS_ENABLED is used.
GIOStatus GlibmmIOChannel::io_read(GIOChannel* channel, char* buf, gsize count,
                                   gsize* bytes_read, GError** /* err */)
#endif
{
  IOChannel *const wrapper = reinterpret_cast<GlibmmIOChannel*>(channel)->wrapper;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
  #endif //GLIBMM_EXCEPTIONS_ENABLED
    return (GIOStatus) wrapper->read_vfunc(buf, count, *bytes_read);
  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(Glib::Error& error)
  {
    error.propagate(err);
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  return G_IO_STATUS_ERROR;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
GIOStatus GlibmmIOChannel::io_write(GIOChannel* channel, const char* buf, gsize count,
                                    gsize* bytes_written, GError** err)
#else
//Avoid an unused parameter warning when GLIBMM_EXCEPTIONS_ENABLED is used.
GIOStatus GlibmmIOChannel::io_write(GIOChannel* channel, const char* buf, gsize count,
                                    gsize* bytes_written, GError** /* err */)
#endif
{
  IOChannel *const wrapper = reinterpret_cast<GlibmmIOChannel*>(channel)->wrapper;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
  #endif //GLIBMM_EXCEPTIONS_ENABLED
    return (GIOStatus) wrapper->write_vfunc(buf, count, *bytes_written);
  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(Glib::Error& error)
  {
    error.propagate(err);
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  return G_IO_STATUS_ERROR;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
GIOStatus GlibmmIOChannel::io_seek(GIOChannel* channel, gint64 offset, GSeekType type, GError** err)
#else
//Avoid an unused parameter warning when GLIBMM_EXCEPTIONS_ENABLED is used.
GIOStatus GlibmmIOChannel::io_seek(GIOChannel* channel, gint64 offset, GSeekType type, GError** /* err */)
#endif
{
  IOChannel *const wrapper = reinterpret_cast<GlibmmIOChannel*>(channel)->wrapper;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
  #endif //GLIBMM_EXCEPTIONS_ENABLED
    return (GIOStatus) wrapper->seek_vfunc(offset, (SeekType) type);
  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(Glib::Error& error)
  {
    error.propagate(err);
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  return G_IO_STATUS_ERROR;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
GIOStatus GlibmmIOChannel::io_close(GIOChannel* channel, GError** err)
#else
//Avoid an unused parameter warning when GLIBMM_EXCEPTIONS_ENABLED is used.
GIOStatus GlibmmIOChannel::io_close(GIOChannel* channel, GError** /* err */)
#endif
{
  IOChannel *const wrapper = reinterpret_cast<GlibmmIOChannel*>(channel)->wrapper;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
  #endif //GLIBMM_EXCEPTIONS_ENABLED
    return (GIOStatus) wrapper->close_vfunc();
  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(Glib::Error& error)
  {
    error.propagate(err);
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED
 

  return G_IO_STATUS_ERROR;
}

// static
GSource* GlibmmIOChannel::io_create_watch(GIOChannel* channel, GIOCondition condition)
{
  IOChannel *const wrapper = reinterpret_cast<GlibmmIOChannel*>(channel)->wrapper;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
  #endif //GLIBMM_EXCEPTIONS_ENABLED
    const Glib::RefPtr<Source> source = wrapper->create_watch_vfunc((IOCondition) condition);
    return (source) ? source->gobj_copy() : 0;
  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  return 0;
}

// static
void GlibmmIOChannel::io_free(GIOChannel* channel)
{
  if(IOChannel *const wrapper = reinterpret_cast<GlibmmIOChannel*>(channel)->wrapper)
  {
    wrapper->gobject_ = 0;
    delete wrapper;
  }

  g_free(channel);
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
GIOStatus GlibmmIOChannel::io_set_flags(GIOChannel* channel, GIOFlags flags, GError** err)
#else
//Avoid an unused parameter warning when GLIBMM_EXCEPTIONS_ENABLED is used.
GIOStatus GlibmmIOChannel::io_set_flags(GIOChannel* channel, GIOFlags flags, GError** /* err */)
#endif
{
  IOChannel *const wrapper = reinterpret_cast<GlibmmIOChannel*>(channel)->wrapper;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
  #endif //GLIBMM_EXCEPTIONS_ENABLED
    return (GIOStatus) wrapper->set_flags_vfunc((IOFlags) flags);
  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(Glib::Error& error)
  {
    error.propagate(err);
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  return G_IO_STATUS_ERROR;
}

// static
GIOFlags GlibmmIOChannel::io_get_flags(GIOChannel* channel)
{
  IOChannel *const wrapper = reinterpret_cast<GlibmmIOChannel*>(channel)->wrapper;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
  #endif //GLIBMM_EXCEPTIONS_ENABLED
    return (GIOFlags) wrapper->get_flags_vfunc();
  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(...)
  {
    Glib::exception_handlers_invoke();
  }
  #endif //GLIBMM_EXCEPTIONS_ENABLED

  return GIOFlags(0);
}

} // namespace Glib


namespace
{
} // anonymous namespace


Glib::IOChannelError::IOChannelError(Glib::IOChannelError::Code error_code, const Glib::ustring& error_message)
:
  Glib::Error (G_IO_CHANNEL_ERROR, error_code, error_message)
{}

Glib::IOChannelError::IOChannelError(GError* gobject)
:
  Glib::Error (gobject)
{}

Glib::IOChannelError::Code Glib::IOChannelError::code() const
{
  return static_cast<Code>(Glib::Error::code());
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
void Glib::IOChannelError::throw_func(GError* gobject)
{
  throw Glib::IOChannelError(gobject);
}
#else
//When not using exceptions, we just pass the Exception object around without throwing it:
std::auto_ptr<Glib::Error> Glib::IOChannelError::throw_func(GError* gobject)
{
  return std::auto_ptr<Glib::Error>(new Glib::IOChannelError(gobject));
}
#endif //GLIBMM_EXCEPTIONS_ENABLED


namespace Glib
{


#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::read(gunichar& thechar)
#else
IOStatus IOChannel::read(gunichar& thechar, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  IOStatus retvalue = ((IOStatus)(g_io_channel_read_unichar(gobj(), &(thechar), &(gerror))));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::read(char* buf, gsize count, gsize& bytes_read)
#else
IOStatus IOChannel::read(char* buf, gsize count, gsize& bytes_read, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  IOStatus retvalue = ((IOStatus)(g_io_channel_read_chars(gobj(), buf, count, &(bytes_read), &(gerror))));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::write(const char* buf, gssize count, gsize& bytes_written)
#else
IOStatus IOChannel::write(const char* buf, gssize count, gsize& bytes_written, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  IOStatus retvalue = ((IOStatus)(g_io_channel_write_chars(gobj(), buf, count, &(bytes_written), &(gerror))));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::write(gunichar unichar)
#else
IOStatus IOChannel::write(gunichar unichar, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  IOStatus retvalue = ((IOStatus)(g_io_channel_write_unichar(gobj(), unichar, &(gerror))));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::seek(gint64 offset, SeekType type)
#else
IOStatus IOChannel::seek(gint64 offset, SeekType type, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  IOStatus retvalue = ((IOStatus)(g_io_channel_seek_position(gobj(), offset, ((GSeekType)(type)), &(gerror))));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::flush()
#else
IOStatus IOChannel::flush(std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  IOStatus retvalue = ((IOStatus)(g_io_channel_flush(gobj(), &(gerror))));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::close(bool flush)
#else
IOStatus IOChannel::close(bool flush, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  IOStatus retvalue = ((IOStatus)(g_io_channel_shutdown(gobj(), static_cast<int>(flush), &(gerror))));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

gsize IOChannel::get_buffer_size() const
{
  return g_io_channel_get_buffer_size(const_cast<GIOChannel*>(gobj()));
}

void IOChannel::set_buffer_size(gsize size)
{
g_io_channel_set_buffer_size(gobj(), size); 
}

IOFlags IOChannel::get_flags() const
{
  return ((IOFlags)(g_io_channel_get_flags(const_cast<GIOChannel*>(gobj()))));
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
IOStatus IOChannel::set_flags(IOFlags flags)
#else
IOStatus IOChannel::set_flags(IOFlags flags, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  GError* gerror = 0;
  IOStatus retvalue = ((IOStatus)(g_io_channel_set_flags(gobj(), ((GIOFlags)(flags)), &(gerror))));
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  return retvalue;

}

void IOChannel::set_buffered(bool buffered)
{
g_io_channel_set_buffered(gobj(), static_cast<int>(buffered)); 
}

bool IOChannel::get_buffered() const
{
  return g_io_channel_get_buffered(const_cast<GIOChannel*>(gobj()));
}

IOCondition IOChannel::get_buffer_condition() const
{
  return ((IOCondition)(g_io_channel_get_buffer_condition(const_cast<GIOChannel*>(gobj()))));
}

bool IOChannel::get_close_on_unref() const
{
  return g_io_channel_get_close_on_unref(const_cast<GIOChannel*>(gobj()));
}

void IOChannel::set_close_on_unref(bool do_close)
{
g_io_channel_set_close_on_unref(gobj(), static_cast<int>(do_close)); 
}


} // namespace Glib


