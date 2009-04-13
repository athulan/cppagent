// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GIOMM_FILEINFO_H
#define _GIOMM_FILEINFO_H


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

#include <glibmm/arrayhandle.h>
#include <glibmm/object.h>
#include <glibmm/timeval.h>
#include <giomm/fileattributeinfolist.h>
#include <giomm/icon.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GFileInfo GFileInfo;
typedef struct _GFileInfoClass GFileInfoClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gio
{ class FileInfo_Class; } // namespace Gio
namespace Gio
{

// Rename FILE_TYPE_UNKNOWN to FILE_TYPE_NOT_KNOWN because the former is a
// define in a Windows header (winbase.h, included from windows.h).
/** @addtogroup giommEnums Enums and Flags */

/**
 * @ingroup giommEnums
 */
enum FileType
{
  FILE_TYPE_NOT_KNOWN,
  FILE_TYPE_REGULAR,
  FILE_TYPE_DIRECTORY,
  FILE_TYPE_SYMBOLIC_LINK,
  FILE_TYPE_SPECIAL,
  FILE_TYPE_SHORTCUT,
  FILE_TYPE_MOUNTABLE
};


// Provide FILE_TYPE_UNKNOWN for backwards compatibility.
#ifndef DOXYGEN_SHOULD_SKIP_THIS
#ifndef FILE_TYPE_UNKNOWN
const FileType FILE_TYPE_UNKNOWN = FILE_TYPE_NOT_KNOWN;
#endif
#endif

//TODO: attribute strings

/** FileAttributeMatcher allows for searching through a FileInfo for attributes.
 *
 * @newin2p16
 */
class FileAttributeMatcher
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef FileAttributeMatcher CppObjectType;
  typedef GFileAttributeMatcher BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


  // For use with Glib::RefPtr<> only.
  void reference()   const;
  void unreference() const;

  ///Provides access to the underlying C instance.
  GFileAttributeMatcher*       gobj();

  ///Provides access to the underlying C instance.
  const GFileAttributeMatcher* gobj() const;

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GFileAttributeMatcher* gobj_copy() const;

protected:
  // Do not derive this.  Gio::FileAttributeMatcher can neither be constructed nor deleted.
  FileAttributeMatcher();
  void operator delete(void*, size_t);

private:
  // noncopyable
  FileAttributeMatcher(const FileAttributeMatcher&);
  FileAttributeMatcher& operator=(const FileAttributeMatcher&);


public:
  /** Creates a new file attribute matcher, which matches attributes against a given string. 
   * The attribute string should be formatted with specific keys separated from namespaces with a double colon. 
   * Several "namespace::key" strings may be concatenated with a single comma (e.g. "standard::type,standard::is-hidden"). 
   * The wildcard "*" may be used to match all keys and namespaces, or "namespace::*" will match all keys in a given namespace.
   *
   * @param attributes The attributes string.
   * @result a new FileAttributeMatcher.
   */
  static Glib::RefPtr<FileAttributeMatcher> create(const std::string& attributes = "*");

  
  /** Checks if an attribute will be matched by an attribute matcher. If 
   * the matcher was created with the "*" matching string, this function
   * will always return <tt>true</tt>.
   * @param attribute A file attribute key.
   * @return <tt>true</tt> if @a attribute matches @a matcher. <tt>false</tt> otherwise.
   */
  bool matches(const std::string& full_name) const;
  
  /** Checks if a attribute matcher only matches a given attribute. Always
   * Returns: <tt>true</tt> if the matcher only matches @a attribute. <tt>false</tt> otherwise.
   * @param attribute A file attribute key.
   * @return <tt>true</tt> if the matcher only matches @a attribute. <tt>false</tt> otherwise.
   */
  bool matches_only(const std::string& full_name) const;
  
  /** Checks if the matcher will match all of the keys in a given namespace.
   * This will always return <tt>true</tt> if a wildcard character is in use (e.g. if 
   * matcher was created with "standard::*" and @a ns is "standard", or if matcher was created
   * using "*" and namespace is anything.) 
   * 
   * TODO: this is awkwardly worded.
   * @param ns A string containing a file attribute namespace.
   * @return <tt>true</tt> if the matcher matches all of the entries
   * in the given @a ns, <tt>false</tt> otherwise.
   */
  bool enumerate_namespace(const std::string& ns);
  
  /** Gets the next matched attribute from a FileAttributeMatcher.
   * @return A string containing the next attribute or <tt>0</tt> if 
   * no more attribute exist.
   */
  std::string enumerate_next();


};

/** FileInfo implements methods for getting information that all files should contain, and allows for manipulation of extended attributes.
 * See FileAttribute for more information on how GIO handles file attributes.
 *
 * To obtain a FileInfo for a File, use File::query_info() (or its async variant).
 * To obtain a FileInfo for a file input or output stream, use FileInput::stream_query_info() or FileOutput::stream_query_info() 
 * (or their async variants).
 *
 * FileAttributeMatcher allows for searching through a FileInfo for attributes.
 */

class FileInfo : public Glib::Object
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  typedef FileInfo CppObjectType;
  typedef FileInfo_Class CppClassType;
  typedef GFileInfo BaseObjectType;
  typedef GFileInfoClass BaseClassType;

private:  friend class FileInfo_Class;
  static CppClassType fileinfo_class_;

private:
  // noncopyable
  FileInfo(const FileInfo&);
  FileInfo& operator=(const FileInfo&);

protected:
  explicit FileInfo(const Glib::ConstructParams& construct_params);
  explicit FileInfo(GFileInfo* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  virtual ~FileInfo();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GFileInfo*       gobj()       { return reinterpret_cast<GFileInfo*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GFileInfo* gobj() const { return reinterpret_cast<GFileInfo*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GFileInfo* gobj_copy();

private:


public:
  FileInfo();

  
  /** Duplicates a file info structure.
   * @return A duplicate FileInfo of @a other.
   */
  Glib::RefPtr<FileInfo> dup() const;
  
  /** Copies all of the FileAttribute&lt;!-- --&gt;s from @a src_info to @a dest_info.
   * @param dest_info Destination to copy attributes to.
   */
  void copy_into(Glib::RefPtr<FileInfo>& dest) const;
  
  /** Checks if a file info structure has an attribute named @a attribute.
   * @param attribute A file attribute key.
   * @return <tt>true</tt> if @a Ginfo has an attribute named @a attribute, 
   * <tt>false</tt> otherwise.
   */
  bool has_attribute(const std::string& attribute) const;
  
  /** Lists the file info structure's attributes.
   * @param name_space A file attribute key's namespace.
   * @return A null-terminated array of strings of all of the 
   * possible attribute types for the given @a name_space, or 
   * <tt>0</tt> on error.
   */
  Glib::StringArrayHandle list_attributes(const std::string& name_space) const;
  
  /** Gets the attribute type for an attribute key.
   * @param attribute A file attribute key.
   * @return A FileAttributeType for the given @a attribute, or 
   * FILE_ATTRIBUTE_TYPE_INVALID if the key is invalid.
   */
  FileAttributeType get_attribute_type(const std::string& attribute) const;
  
  /** Removes all cases of @a attribute from @a info if it exists.
   * @param attribute A file attribute key.
   */
  void remove_attribute(const std::string& attribute);
  
  /** Gets the value of a string attribute. If the attribute does 
   * not contain a string, <tt>0</tt> will be returned.
   * @param attribute A file attribute key.
   * @return The contents of the @a attribute value as a string, or 
   * <tt>0</tt> otherwise.
   */
  std::string get_attribute_string(const std::string& attribute) const;
  
  /** Gets the value of a attribute, formated as a string.
   * This escapes things as needed to make the string valid
   * utf8.
   * @param attribute A file attribute key.
   * @return A UTF-8 string associated with the given @a attribute.
   * When you're done with the string it must be freed with Glib::free().
   */
  Glib::ustring get_attribute_as_string(const std::string& attribute) const;
  
  /** Gets the value of a byte string attribute. If the attribute does 
   * not contain a byte string, <tt>0</tt> will be returned.
   * @param attribute A file attribute key.
   * @return The contents of the @a attribute value as a byte string, or 
   * <tt>0</tt> otherwise.
   */
  std::string get_attribute_byte_string(const std::string& attribute) const;
  
  /** Gets the value of a boolean attribute. If the attribute does not
   * contain a boolean value, <tt>false</tt> will be returned.
   * @param attribute A file attribute key.
   * @return The boolean value contained within the attribute.
   */
  bool get_attribute_boolean(const std::string& attribute) const;
  
  /** Gets an unsigned 32-bit integer contained within the attribute. If the 
   * attribute does not contain an unsigned 32-bit integer, or is invalid, 
   * 0 will be returned.
   * @param attribute A file attribute key.
   * @return An unsigned 32-bit integer from the attribute.
   */
  guint32 get_attribute_uint32(const std::string& attribute) const;
  
  /** Gets a signed 32-bit integer contained within the attribute. If the 
   * attribute does not contain a signed 32-bit integer, or is invalid, 
   * 0 will be returned.
   * @param attribute A file attribute key.
   * @return A signed 32-bit integer from the attribute.
   */
  gint32 get_attribute_int32(const std::string& attribute) const;
  
  /** Gets a unsigned 64-bit integer contained within the attribute. If the 
   * attribute does not contain an unsigned 64-bit integer, or is invalid, 
   * 0 will be returned.
   * @param attribute A file attribute key.
   * @return A unsigned 64-bit integer from the attribute.
   */
  guint64 get_attribute_uint64(const std::string& attribute) const;
  
  /** Gets a signed 64-bit integer contained within the attribute. If the 
   * attribute does not contain an signed 64-bit integer, or is invalid, 
   * 0 will be returned.
   * @param attribute A file attribute key.
   * @return A signed 64-bit integer from the attribute.
   */
  gint64 get_attribute_int64(const std::string& attribute) const;
  
  /** Gets the value of a Object attribute. If the attribute does 
   * not contain a Object, <tt>0</tt> will be returned.
   * @param attribute A file attribute key.
   * @return A Object associated with the given @a attribute, or
   * <tt>0</tt> otherwise.
   */
  Glib::RefPtr<Glib::Object> get_attribute_object(const std::string& attribute) const;
  
  /** Sets the @a attribute to contain the given @a attr_value, 
   * if possible.
   * @param attribute A file attribute key.
   * @param attr_value A string.
   */
  void set_attribute_string(const std::string& attribute, const std::string& value);
  
  /** Sets the @a attribute to contain the given @a attr_value, 
   * if possible.
   * @param attribute A file attribute key.
   * @param attr_value A byte string.
   */
  void set_attribute_byte_string(const std::string& attribute, const std::string& value);
  
  /** Sets the @a attribute to contain the given @a attr_value, 
   * if possible.
   * @param attribute A file attribute key.
   * @param attr_value A boolean value.
   */
  void set_attribute_boolean(const std::string& attribute, bool value);
  
  /** Sets the @a attribute to contain the given @a attr_value, 
   * if possible.
   * @param attribute A file attribute key.
   * @param attr_value An unsigned 32-bit integer.
   */
  void set_attribute_uint32(const std::string& attribute, guint32 value);
  
  /** Sets the @a attribute to contain the given @a attr_value, 
   * if possible.
   * @param attribute A file attribute key.
   * @param attr_value A signed 32-bit integer.
   */
  void set_attribute_int32(const std::string& attribute, gint32 value);
  
  /** Sets the @a attribute to contain the given @a attr_value, 
   * if possible.
   * @param attribute A file attribute key.
   * @param attr_value An unsigned 64-bit integer.
   */
  void set_attribute_uint64(const std::string& attribute, guint64 value);
  
  /** Sets the @a attribute to contain the given @a attr_value, 
   * if possible.
   * @param attribute Attribute name to set.
   * @param attr_value Int64 value to set attribute to.
   */
  void set_attribute_int64(const std::string& attribute, gint64 value);
  
  /** Sets the @a attribute to contain the given @a attr_value, 
   * if possible.
   * @param attribute A file attribute key.
   * @param attr_value A Object.
   */
  void set_attribute_object(const std::string& attribute, const Glib::RefPtr<Glib::Object>& object);
  
  /** Clears the status information from @a info.
   */
  void clear_status();

  // helper getters

  
  /** Gets a file's type (whether it is a regular file, symlink, etc). 
   * This is different from the file's content type, see g_file_info_get_content_type().
   * @return A FileType for the given file.
   */
  FileType get_file_type() const;
  
  /** Checks if a file is hidden.
   * @return <tt>true</tt> if the file is a hidden file, <tt>false</tt> otherwise.
   */
  bool is_hidden() const;
  
  /** Checks if a file is a backup file.
   * @return <tt>true</tt> if file is a backup file, <tt>false</tt> otherwise.
   */
  bool is_backup() const;
  
  /** Checks if a file is a symlink.
   * @return <tt>true</tt> if the given @a info is a symlink.
   */
  bool is_symlink() const;
  
  /** Gets the name for a file.
   * @return A string containing the file name.
   */
  std::string get_name() const;
  
  /** Gets a display name for a file.
   * @return A string containing the display name.
   */
  std::string get_display_name() const;
  
  /** Gets the edit name for a file.
   * @return A string containing the edit name.
   */
  std::string get_edit_name() const;

  
  /** Gets the icon for a file.
   * @return Icon for the given @a info.
   */
  Glib::RefPtr<Icon> get_icon();
  
  /** Gets the icon for a file.
   * @return Icon for the given @a info.
   */
  Glib::RefPtr<const Icon> get_icon() const;

  
  /** Gets the file's content type.
   * @return A string containing the file's content type.s.
   */
  std::string get_content_type() const;
  
  /** Gets the file's size.
   * @return A #goffset containing the file's size.
   */
  goffset get_size() const;

  Glib::TimeVal modification_time() const;

  
  /** Gets the symlink target for a given FileInfo.
   * @return A string containing the symlink target.
   */
  std::string get_symlink_target() const;
  
  /** Gets the entity tag for a given 
   * FileInfo. See FILE_ATTRIBUTE_ETAG_VALUE.
   * @return A string containing the value of the "etag:value" attribute.
   */
  std::string get_etag() const;
  
  /** Gets the value of the sort_order attribute from the FileInfo.
   * See FILE_ATTRIBUTE_STANDARD_SORT_ORDER.
   * @return A #gint32 containing the value of the "standard::sort_order" attribute.
   */
  gint32 get_sort_order() const;
  
  /** Sets @a mask on @a info to match specific attribute types.
   * @param mask A FileAttributeMatcher.
   */
  void set_attribute_mask(const Glib::RefPtr<FileAttributeMatcher>& mask);
  
  /** Unsets a mask set by g_file_info_set_attribute_mask(), if one
   * is set.
   */
  void unset_attribute_mask();

  // helper setters

  
  /** Sets the file type in a FileInfo to @a type.
   * See FILE_ATTRIBUTE_STANDARD_TYPE.
   * @param type A FileType.
   */
  void set_file_type(FileType type);
  
  /** Sets the "is_hidden" attribute in a FileInfo according to @a is_symlink.
   * See FILE_ATTRIBUTE_STANDARD_IS_HIDDEN.
   * @param is_hidden A <tt>bool</tt>.
   */
  void set_is_hidden(bool is_hidden = true);
  
  /** Sets the "is_symlink" attribute in a FileInfo according to @a is_symlink.
   * See FILE_ATTRIBUTE_STANDARD_IS_SYMLINK.
   * @param is_symlink A <tt>bool</tt>.
   */
  void set_is_symlink(bool is_symlink = true);
  
  /** Sets the name attribute for the current FileInfo. 
   * See FILE_ATTRIBUTE_STANDARD_NAME.
   * @param name A string containing a name.
   */
  void set_name(const std::string& name);
  
  /** Sets the display name for the current FileInfo.
   * See FILE_ATTRIBUTE_STANDARD_DISPLAY_NAME.
   * @param display_name A string containing a display name.
   */
  void set_display_name(const std::string& display_name);
  
  /** Sets the edit name for the current file.
   * See FILE_ATTRIBUTE_STANDARD_EDIT_NAME.
   * @param edit_name A string containing an edit name.
   */
  void set_edit_name(const std::string& edit_name);
  
  /** Sets the icon for a given FileInfo. 
   * See FILE_ATTRIBUTE_STANDARD_ICON.
   * @param icon A Icon.
   */
  void set_icon(const Glib::RefPtr<Icon>& icon);
  
  /** Sets the content type attribute for a given FileInfo.
   * See FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE.
   * @param content_type A content type. See ContentType.
   */
  void set_content_type(const std::string& content_type);
  
  /** Sets the FILE_ATTRIBUTE_STANDARD_SIZE attribute in the file info 
   * to the given size.
   * @param size A #goffset containing the file's size.
   */
  void set_size(goffset size);

  
  /** Sets the FILE_ATTRIBUTE_TIME_MODIFIED attribute in the file
   * info to the given time value.
   * @param mtime A TimeVal.
   */
  void set_modification_time(const Glib::TimeVal& mtime);
  
  /** Sets the FILE_ATTRIBUTE_STANDARD_SYMLINK_TARGET attribute in the file info 
   * to the given symlink target.
   * @param symlink_target A static string containing a path to a symlink target.
   */
  void set_symlink_target(const std::string& symlink_target);
  
  /** Sets the sort order attribute in the file info structure. See 
   * FILE_ATTRIBUTE_STANDARD_SORT_ORDER.
   * @param sort_order A sort order integer.
   */
  void set_sort_order(gint32 sort_order);


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
   * @relates Gio::FileAttributeMatcher
   */
  Glib::RefPtr<Gio::FileAttributeMatcher> wrap(GFileAttributeMatcher* object, bool take_copy = false);

} // namespace Glib


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gio::FileInfo
   */
  Glib::RefPtr<Gio::FileInfo> wrap(GFileInfo* object, bool take_copy = false);
}


#endif /* _GIOMM_FILEINFO_H */

