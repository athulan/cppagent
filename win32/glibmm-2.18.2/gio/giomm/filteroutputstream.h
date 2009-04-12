// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GIOMM_FILTEROUTPUTSTREAM_H
#define _GIOMM_FILTEROUTPUTSTREAM_H


#include <glibmm.h>

// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 2 -*-

/* Copyright (C) 2008 The gtkmm Development Team
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

#include <giomm/outputstream.h>
#include <glibmm/object.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GFilterOutputStream GFilterOutputStream;
typedef struct _GFilterOutputStreamClass GFilterOutputStreamClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gio
{ class FilterOutputStream_Class; } // namespace Gio
namespace Gio
{

//TODO: Proper documentation:

/** Filter Output Stream.
 *
 * @ingroup Streams
 *
 * @newin2p16
 */

class FilterOutputStream : public Gio::OutputStream
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  typedef FilterOutputStream CppObjectType;
  typedef FilterOutputStream_Class CppClassType;
  typedef GFilterOutputStream BaseObjectType;
  typedef GFilterOutputStreamClass BaseClassType;

private:  friend class FilterOutputStream_Class;
  static CppClassType filteroutputstream_class_;

private:
  // noncopyable
  FilterOutputStream(const FilterOutputStream&);
  FilterOutputStream& operator=(const FilterOutputStream&);

protected:
  explicit FilterOutputStream(const Glib::ConstructParams& construct_params);
  explicit FilterOutputStream(GFilterOutputStream* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  virtual ~FilterOutputStream();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GFilterOutputStream*       gobj()       { return reinterpret_cast<GFilterOutputStream*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GFilterOutputStream* gobj() const { return reinterpret_cast<GFilterOutputStream*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GFilterOutputStream* gobj_copy();

private:

public:
  
  /** Gets the base stream for the filter stream.
   * @return A OutputStream.
   */
  Glib::RefPtr<OutputStream> get_base_stream();

  
  /** Gets the base stream for the filter stream.
   * @return A OutputStream.
   */
  Glib::RefPtr<const OutputStream> get_base_stream() const;

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The underlying base stream the io ops will be done on.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::RefPtr<InputStream> > property_base_stream() const;
#endif //#GLIBMM_PROPERTIES_ENABLED


public:

public:
  //C++ methods used to invoke GTK+ virtual functions:
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

protected:
  //GTK+ Virtual Functions (override these to change behaviour):
#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

  //Default Signal Handlers::
#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


};

} // namespace Gio


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gio::FilterOutputStream
   */
  Glib::RefPtr<Gio::FilterOutputStream> wrap(GFilterOutputStream* object, bool take_copy = false);
}


#endif /* _GIOMM_FILTEROUTPUTSTREAM_H */

