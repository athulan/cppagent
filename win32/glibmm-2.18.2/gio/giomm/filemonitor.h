// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GIOMM_FILEMONITOR_H
#define _GIOMM_FILEMONITOR_H


#include <glibmm.h>

// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 2 -*-

/* Copyright (C) 2007 The gtkmm Development Team
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

//#include <giomm/file.h>
#include <glibmm/object.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GFileMonitor GFileMonitor;
typedef struct _GFileMonitorClass GFileMonitorClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gio
{ class FileMonitor_Class; } // namespace Gio
namespace Gio
{

/** @addtogroup giommEnums Enums and Flags */

/**
 * @ingroup giommEnums
 */
enum FileMonitorEvent
{
  FILE_MONITOR_EVENT_CHANGED,
  FILE_MONITOR_EVENT_CHANGES_DONE_HINT,
  FILE_MONITOR_EVENT_DELETED,
  FILE_MONITOR_EVENT_CREATED,
  FILE_MONITOR_EVENT_ATTRIBUTE_CHANGED,
  FILE_MONITOR_EVENT_PRE_UNMOUNT,
  FILE_MONITOR_EVENT_UNMOUNTED
};


class File;

/** Monitors a file or directory for changes.
 * To obtain a FileMonitor for a file or directory, use File::monitor_file() or 
 * File::monitor_directory().
 * 
 * To get informed about changes to the file or directory you are monitoring, 
 * connect to signal_changed.
 *
 * @newin2p16
 */

class FileMonitor : public Glib::Object
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  typedef FileMonitor CppObjectType;
  typedef FileMonitor_Class CppClassType;
  typedef GFileMonitor BaseObjectType;
  typedef GFileMonitorClass BaseClassType;

private:  friend class FileMonitor_Class;
  static CppClassType filemonitor_class_;

private:
  // noncopyable
  FileMonitor(const FileMonitor&);
  FileMonitor& operator=(const FileMonitor&);

protected:
  explicit FileMonitor(const Glib::ConstructParams& construct_params);
  explicit FileMonitor(GFileMonitor* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  virtual ~FileMonitor();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GFileMonitor*       gobj()       { return reinterpret_cast<GFileMonitor*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GFileMonitor* gobj() const { return reinterpret_cast<GFileMonitor*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GFileMonitor* gobj_copy();

private:

protected:

public:
  
  
  /** Cancels a file monitor.
   * @return <tt>true</tt> if monitor was cancelled.
   */
  bool cancel();
  
  /** Returns: <tt>true</tt> if monitor is canceled. <tt>false</tt> otherwise.
   * @return <tt>true</tt> if monitor is canceled. <tt>false</tt> otherwise.
   */
  bool is_cancelled() const;
  
  /** Sets the rate limit to which the @a monitor will report
   * consecutive change events to the same file.
   * @param limit_msecs A integer with the limit in milliseconds to 
   * poll for changes.
   */
  void set_rate_limit(int limit_msecs);

  //g_file_monitor_emit_event is for implementations.
  

  /**
   * @par Prototype:
   * <tt>void on_my_%changed(const Glib::RefPtr<File>& file, const Glib::RefPtr<File>& other_file, FileMonitorEvent event_type)</tt>
   */

  Glib::SignalProxy3< void,const Glib::RefPtr<File>&,const Glib::RefPtr<File>&,FileMonitorEvent > signal_changed();

  
  //_WRAP_VFUNC(bool cancel(), cancel);

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** The limit of the monitor to watch for changes
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<int> property_rate_limit() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
/** The limit of the monitor to watch for changes
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<int> property_rate_limit() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  #ifdef GLIBMM_PROPERTIES_ENABLED
/** Whether the monitor has been cancelled.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<bool> property_cancelled() const;
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
  virtual void on_changed(const Glib::RefPtr<File>& file, const Glib::RefPtr<File>& other_file, FileMonitorEvent event_type);
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
   * @relates Gio::FileMonitor
   */
  Glib::RefPtr<Gio::FileMonitor> wrap(GFileMonitor* object, bool take_copy = false);
}


#endif /* _GIOMM_FILEMONITOR_H */

