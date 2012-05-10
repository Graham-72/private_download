<?php

/**
 * @file
 * Hooks that can be implemented by other modules to extend Private Download.
 */

/**
 * Alter permission to access private files.
 *
 * Note that altering permission will have effect only within the limits of
 * option chosen by admin for "Allow/Deny priority".
 *
 * @param $filepath
 *   The file path, relative to the private download directory.
 *
 * @return
 *   TRUE to allow access, FALSE to deny access, or nothing if the implementing
 *   module is not responsible for the given file.
 */
function hook_private_download_access($filepath) {
  // Never allow access to any file which path contains string 'forbidden'.
  if (strpos($filepath, 'forbidden') !== FALSE) {
    return FALSE;
  }
}
