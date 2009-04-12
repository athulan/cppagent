// Generated by gtkmmproc -- DO NOT MODIFY!


#include <giomm/themedicon.h>
#include <giomm/private/themedicon_p.h>

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

#include <gio/gio.h>

namespace Gio
{

ThemedIcon::ThemedIcon(const std::string& iconname, bool use_default_callbacks)
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(0),
  Glib::Object(Glib::ConstructParams(themedicon_class_.init(), "name",iconname.c_str(),"use-default-fallbacks",gboolean(use_default_callbacks), static_cast<char*>(0)))
{}


} //namespace Gio

namespace
{
} // anonymous namespace


namespace Glib
{

Glib::RefPtr<Gio::ThemedIcon> wrap(GThemedIcon* object, bool take_copy)
{
  return Glib::RefPtr<Gio::ThemedIcon>( dynamic_cast<Gio::ThemedIcon*> (Glib::wrap_auto ((GObject*)(object), take_copy)) );
  //We use dynamic_cast<> in case of multiple inheritance.
}

} /* namespace Glib */


namespace Gio
{


/* The *_Class implementation: */

const Glib::Class& ThemedIcon_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &ThemedIcon_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(g_themed_icon_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:
  Icon::add_interface(get_type());

  }

  return *this;
}

void ThemedIcon_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);

#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
}

#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED

#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED


Glib::ObjectBase* ThemedIcon_Class::wrap_new(GObject* object)
{
  return new ThemedIcon((GThemedIcon*)object);
}


/* The implementation: */

GThemedIcon* ThemedIcon::gobj_copy()
{
  reference();
  return gobj();
}

ThemedIcon::ThemedIcon(const Glib::ConstructParams& construct_params)
:
  Glib::Object(construct_params)
{

}

ThemedIcon::ThemedIcon(GThemedIcon* castitem)
:
  Glib::Object((GObject*)(castitem))
{}


ThemedIcon::~ThemedIcon()
{}


ThemedIcon::CppClassType ThemedIcon::themedicon_class_; // initialize static member

GType ThemedIcon::get_type()
{
  return themedicon_class_.init().get_type();
}

GType ThemedIcon::get_base_type()
{
  return g_themed_icon_get_type();
}


Glib::RefPtr<ThemedIcon> ThemedIcon::create(const std::string& iconname, bool use_default_callbacks)
{
  return Glib::RefPtr<ThemedIcon>( new ThemedIcon(iconname, use_default_callbacks) );
}
void ThemedIcon::prepend_name(const std::string& iconname)
{
g_themed_icon_prepend_name(gobj(), iconname.c_str()); 
}

void ThemedIcon::append_name(const std::string& iconname)
{
g_themed_icon_append_name(gobj(), iconname.c_str()); 
}


#ifdef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED

#ifdef GLIBMM_VFUNCS_ENABLED
#endif //GLIBMM_VFUNCS_ENABLED


} // namespace Gio


