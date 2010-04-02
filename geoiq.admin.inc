<?php

/**
 * @file
 * Administration page callbacks for the geoid module.
 */


function geoiq_admin_settings()
{
 $form['credentials'] = array(
   '#type' => 'fieldset',
   '#title' => 'GeoIQ Credentials',
   '#description' => t("Enter the server address and your GeoCommons user name and password. For security reasons, your password has not been loaded. You will have to enter your password every time you reset this setting."),
 );


   $form['credentials']['geoiq_server_address'] = array(
    '#type' => 'textfield',
    '#title' => 'Server Address',
    '#size' => 80,
    '#default_value' => variable_get('geoiq_server_address', 'http://www.geocommons.com'),
    '#description' => t('Please include the protocol; i.e., http://. Remove trailing slash.'),
  );

  $form['credentials']['geoiq_user_name'] = array(
    '#type' => 'textfield',
    '#title' => 'User Name',
    '#size' => 80,
    '#default_value' => variable_get('geoiq_user_name', ''),
    '#description' => t('Enter your GeoCommons user name'),
  );

  $form['credentials']['geoiq_password'] = array(
    '#type' => 'password_confirm',
    '#description' => 'Re-enter your password when updating any value on this form.',
    '#size' => 80,
    '#description' => t('Enter your GeoCommons password'),
  );

 
  return system_settings_form($form);
}

function geoiq_admin_settings_validate($form, $form_state){
  $server = $form_state['values']['geoiq_server_address'];
  $password = $form_state['values']['geoiq_password'];

  if ($password == ""){
      form_set_error('geoiq_password', t('Password cannot be blank.'));
  }

  if (!isURL($server)){
    form_set_error('geoiq_server_address', t('Please enter a valid server address'));
  }

  if (hasTrailingSlash($server))
  {
     form_set_error('geoiq_server_address', t('Please remove trailing slash'));
  }
}

function hasTrailingSlash($var){
  $result = false;
  $last = substr($var, -1);
  
  if ($last == '/')
    $result = true;

  return $result;
}

function isURL($url = NULL) {
        if($url==NULL) return false;

        $protocol = '(http://|https://)';
        $allowed = '([a-z0-9]([-a-z0-9]*[a-z0-9]+)?)';

        $regex = "^". $protocol . // must include the protocol
                         '(' . $allowed . '{1,63}\.)+'. // 1 or several sub domains with a max of 63 chars
                         '[a-z]' . '{2,6}'; // followed by a TLD
        if(eregi($regex, $url)==true) return true;
        else return false;
}


function geoiq_admin_nodes(){

  $options = node_get_types('names');

  $form['geoiq_nodes'] = array(
     '#type' => 'fieldset',
     '#title' => 'GeoIQ content types',
     '#description' => t('Select the content types that you wish to add the capability to search for and add GeoCommons maps'),
    );

  $form['geoiq_nodes']['geoiq_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#options' => $options,
    '#default_value' => variable_get('geoiq_node_types', array()),
    );  
  
    
  return system_settings_form($form);
}

function geoiq_admin_feed_settings()
{
   $form['geoiq_feeds'] = array(
   '#type' => 'fieldset',
   '#title' => 'GeoIQ Credentials',
   '#description' => 'Set up feeds as a GeoIQ source.',
 );

   $form['geoiq_feeds']['geoiq_message_feedbacak'] = array(
     '#type' => 'markup',
     '#value' => '<div id="geoiq-feed-message"></div>',
   );

  $form['geoiq_feeds']['geoiq_feeds'] = array(
   '#type' => 'textfield',
   '#title' => 'Enter Feed', 
   '#description' => 'Enter any GeoRSS or kml feed.',
   '#id' => 'geoiq-feed-address',
   '#size' => 80,
  );

  $form['geoiq_feeds']['geoiq_results'] = array(
    '#type' => 'markup',
    '#value' => '<p><input type="button" id="geoiq-submit-feed" value="Insert Feed"/><img id="geoiq-ajax-spinner" style="visibility:hidden;" src="' . base_path() . drupal_get_path('module', 'geoiq') . '/ajax-loader.gif" /></p>',
    '#size' => 80,
  );

  return $form;
}
 
