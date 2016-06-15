<?php

/**
 * Private Download admin configuration form.
 */
function private_download_admin_form($form, &$form_state) {
  $header = variable_get('private_download_header', "Content-Transfer-Encoding: binary\nCache-Control: private");
  $form['private_download_header'] = array(
    '#type' => 'textarea',
    '#title' => t('file headers'),
    '#default_value' => $header,
    '#required' => TRUE,
    '#rows' => 4,
    '#description' => t('Enter a list of header attributes, one entry per line.'),
  );

  $form['private_download_disposition'] = array(
    '#type' => 'radios',
    '#title' => t('Download behavior'),
    '#default_value' => variable_get('private_download_disposition', 'attachment'),
    '#options' => array(
      'attachment' => t('attachment - always trigger a "save as..." dialog'),
      'inline' => t('inline - attempt to display the file within the browser window if its type matches one of the patterns below'),
    ),
    '#required' => TRUE,
  );

  $inline_patterns = variable_get('private_download_inline_patterns', array('^text/', '^image/', '\bflash$', '\bpdf$'));
  $form['private_download_inline_patterns'] = array(
    '#type' => 'textarea',
    '#title' => t('Inline type patterns'),
    '#default_value' => implode("\n", $inline_patterns),
    '#rows' => 4,
    '#description' => t('Enter a list of MIME type patterns, one entry per line. This has only effect when option <em>inline</em> is selected in field <em>Download behavior</em> above.'),
  );

  $form['private_download_allowdeny_priority'] = array(
    '#type' => 'radios',
    '#title' => t('Allow/Deny priority'),
    '#default_value' => variable_get('private_download_allowdeny_priority', 'deny'),
    '#options' => array(
      'deny' => t('<em>deny</em> has priority over <em>allow</em>'),
      'allow' => t('<em>allow</em> has priority over <em>deny</em>'),
    ),
    '#required' => TRUE,
    '#disabled' => !count(module_implements('private_download_access')),
  );
  if (count(module_implements('private_download_access'))) {
    $form['private_download_allowdeny_priority']['#description'] = t('Determines behavior when there are installed modules altering private download permissions: when <em>deny</em> has priority over <em>allow</em>, no module can allow but only deny access; when <em>allow</em> has priority over <em>deny</em>, any module may allow access bypassing the <em>access private download directory</em> permission.');
  }
  else {
    $form['private_download_allowdeny_priority']['#disabled'] = TRUE;
    $form['private_download_allowdeny_priority']['#description'] = t('This option has no effect here as there is currently no installed module altering private download permissions.');
  }

  $form['#submit'][] = 'private_download_admin_submit_handler';
  return system_settings_form($form);
}

/**
 * Validate handler.
 */
function private_download_admin_form_validate($form, &$form_state) {
  $inline_patterns = array_filter(array_map('trim', explode("\n", $form_state['values']['private_download_inline_patterns'])));
  form_set_value($form['private_download_inline_patterns'], $inline_patterns, $form_state);
}

/**
 * Custom submit handler.
 */
function private_download_admin_submit_handler($form, &$form_state) {
  drupal_set_message(t('Remember to set private download directory access permissions for permitted roles on the !permissions_url page.', array('!permissions_url' => l('permissions', 'admin/people/permissions'))));
}
