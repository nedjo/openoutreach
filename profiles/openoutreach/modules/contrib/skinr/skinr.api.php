<?php
/**
 * @file
 * This file contains no working PHP code; it exists to provide additional documentation
 * for doxygen as well as to document hooks in the standard Drupal manner.
 */

/**
 * @mainpage Skinr API Manual
 *
 * Topics:
 * - @ref skinr_hooks
 */

/**
 * @defgroup skinr_hooks Skinrs hooks
 * @{
 * Hooks that can be implemented by other modules in order to implement the
 * Skinr API.
 */

/**
 * Configure Skinr for this module.
 *
 * This hook should be placed in MODULENAME.skinr.inc and it will be auto-loaded.
 * This must either be in the same directory as the .module file or in a subdirectory
 * named 'includes'.
 *
 * @return
 *   An array of element types this module supports.
 */
function hook_skinr_config() {
  return array('block');
}

/**
 * Provide a list of all available theme hooks for a given element.
 *
 * @param $module
 *   The module implementing given element.
 * @param $element
 *   An element.
 *
 * @return
 *   An array of theme hooks.
 */
function hook_skinr_theme_hooks($module, $element) {
  $theme_hooks = array();

  if ($module == 'node') {
    $theme_hooks =  array(
      'node_' . $element,
      'node',
    );
  }

  return $theme_hooks;
}

/**
 * Perform alterations to theme hooks before widgets are rendered.
 *
 * @param $theme_hooks
 *   An array of theme hooks.
 * @param $module
 *   The module implementing given element.
 * @param $element
 *   An element.
 */
function hook_skinr_theme_hooks_alter(&$theme_hooks, $module, $element) {
  if ($module == 'node') {
    array_unshift($theme_hooks, 'node_' . $element . '_custom');
  }
}

/**
 * Return an array of element ids.
 *
 * @todo Needs a better description.
 *
 * @param $variables
 *   The variables array from skinr_preprocess().
 * @param $hook
 *   The name of the theme hook.
 * @param $op
 *   The operation being performed:
 *   - 'preprocess'
 *   - 'contextual_links'
 *
 * @return
 *   An array of element arrays, keyed by element type. Example:
 * @code
 *   array(
 *     'block' => array('system__navigation'),
 *   );
 * @endcode
 *
 * @see skinr_preprocess()
 */
function hook_skinr_elements(&$variables, $hook, $op) {
  $elements = array();
  if ($hook == 'block') {
    $elements['block'] = array($variables['block']->module . '__' . $variables['block']->delta);
  }
  return $elements;
}

/**
 * Define the API version of Skinr your code is compatible with.
 *
 * This is required when creating a new Skinr plugin. It checks to make sure
 * your Skins are compatible with the installed version of Skinr and takes care
 * of loading the include files.
 *
 * @return
 *   An associative array describing Skinr API integration:
 *   - directory: (optional) The name of a sub-directory, in which include files
 *     containing skin or group definitions may be found.
 *   - path: (optional) The path to the directory containing the directory
 *     specified in 'directory'. Defaults to the path of the module or theme
 *     implementing the hook.
 *   In case no Skinr plugin include files exist for your implementation, simply
 *   define the function with an empty function body.
 *
 * The "hook" prefix is substituted with the name of the module or theme that
 * implements it, e.g. THEME_skinr_api_VERSION() in template.php, or
 * MODULE_skinr_api_VERSION() in MODULE.module.
 *
 * VERSION is normally identical to Skinr's major version; e.g., "2".
 */
function hook_skinr_api_VERSION() {
  return array(
    'path' => drupal_get_path('module', 'mymodule'),
    'directory' => 'skins',
  );
}

/**
 * Define the skin(s) for this Skinr plugin.
 *
 * Each skin definition consists of properties that define its form element and
 * settings that are needed to make it work, such as the class(es) Skinr should
 * apply, which files it should load, whether or not it should be disabled by
 * default and which theme hook(s) it was designed to work with.
 *
 * Each skin name must be unique. Skins cannot have the same name even if they
 * are located in different plugins. It is recommended to prefix the name of
 * each skin with the name of the theme or module implementing it.
 *
 * Skin settings:
 * - title (required): Title of the skin form element.
 * - description (optional): Description of the skin form element.
 * - group (optional): The group the skin is attached to; defaults to a Skinr
 *   provided group labeled "General."
 * - type (optional): The type of form element. Allowed values:
 *   - checkboxes (default): Useful when single or multiple options can be
 *     chosen. This type does not need to be set manually. Skinr will apply
 *     it by default.
 *   - select: Useful when a single option can be chosen, but many exist.
 *   - radios: Useful when a single option can be chosen and only a few options
 *     exist.
 * - weight (discouraged): Sets the weight of the skin inside the group; NULL
 *   by default. weight should not be set on each individual skin. Instead, it
 *   should be used sparingly where positioning a skin at the very top or
 *   bottom is desired.
 * - attached (optional): A array containing information about CSS and
 *   JavaScript files the skin requires. Each entry is an array keyed by type:
 *   - css (optional): Maps to the functionality of drupal_add_css() with one
 *     exception: paths are automatically assumed relative to the plugin
 *     directory, unless external. Examples:
 *     - Simple:
 *       'css' => array('css/skin-name.css')
 *     - Advanced:
 *       'css' => array(
 *         array('css/skin-name-ie.css', array(
 *           'media' => 'screen',
 *           'browsers' => array('IE' => 'lte IE 8'),
 *         ),
 *       )
 *   - js (optional): Maps to the functionality of drupal_add_js() with one
 *     exception: paths are automatically assumed as relative to the plugin
 *     directory, unless external. Examples:
 *     - Simple:
 *       'js' => array('js/skin-name.js')
 *     - Advanced:
 *       'js' => array(
 *         array(
 *           'js/skin-name-advanced.js',
 *           array(
 *             'scope' => 'footer',
 *             'group' => JS_THEME,
 *         ),
 *       )
 * - options (required): An array containing one or more options (also arrays)
 *   for the user to choose from when applying skins. Each option key should be
 *   a machine name describing the option. An option should including the
 *   following keys:
 *   - title (required): The option label.
 *   - class (required): An array containing one or more classes the skin
 *     should apply. All classes should be entered as an array: For example:
 *     'class' => array('class-b', 'class-b')
 *   - attached (optional): Same syntax as above, but applies to a specific
 *     option only.
 * - theme hooks (optional): An array containing certain allowed theme hooks,
 *   which allow you to limit where the skin can be used. Allowed options
 *   include: block, block__MODULE, comment_wrapper,comment__wrapper_NODETYPE,
 *   node, node__NODETYPE, region, region__REGIONNAME, panels_display,
 *   panels_region, panels_pane, views_view, views_view__STYLENAME,
 *   views_view__DISPLAYNAME, and views_view__VIEWNAME.
 * - default status (optional): Skins are disabled by default to keep UI
 *   clutter to a minimum. In some cases, like contrib themes, it makes sense to
 *   enable skins which are required to make the theme work properly by default.
 *   Setting this property to 1 will cause it to be enabled by default for all
 *   installed themes.
 * - status: (optional) An associative array whose keys are theme names and
 *   whose corresponding values denote the desired default status for the
 *   particular theme.
 *
 * The "hook" prefix is substituted with the name of the module or theme
 * implementing it.
 */
function hook_skinr_skin_info() {
  $skins['skinr_menus'] = array(
    'title' => t('Menu styles'),
    'description' => t('Select a style to use for the main navigation.'),
    'type' => 'select',
    'group' => 'skinr_menus',
    'theme hooks' => array('block__menu', 'block__menu_block'),
    'attached' => array(
      'css' => array('css/nav.css'),
    ),
    'options' => array(
      'one_level' => array(
        'title' => t('Standard (1 level) - No colors'),
        'class' => array('nav'),
      ),
      'menu_a' => array(
        'title' => t('Standard (1 level) - Green'),
        'class' => array('nav', 'nav-a'),
        'attached' => array('css' => array('css/nav-colors.css')),
      ),
      'menu_b' => array(
        'title' => t('Standard (1 level) - Blue'),
        'class' => array('nav', 'nav-b'),
        'attached' => array('css' => array('css/nav-colors.css')),
      ),
      'menu_c' => array(
        'title' => t('Dropdowns - No colors'),
        'class' => array('nav', 'nav-dd'),
        'attached' => array(
          'css' => array('css/nav-dd.css'),
          'js' => array('js/dropdown.js'),
        ),
      ),
      'menu_d' => array(
        'title' => t('Dropdowns - Green'),
        'class' => array('nav', 'nav-dd', 'nav-a'),
        'attached' => array(
          'css' => array('css/nav-dd.css'),
          'js' => array('js/dropdown.js'),
        ),
      ),
      'menu_e' => array(
        'title' => t('Dropdowns - Blue'),
        'class' => array('nav', 'nav-dd', 'nav-b'),
        'attached' => array(
          'css' => array('css/nav-dd.css'),
          'js' => array('js/dropdown.js'),
        ),
      ),
    ),
    // Optional: Specify a global default status for this skin, making it
    // available or unavailable to all themes.
    'default status' => 0,
    // Optional: Specify a default status for a particular theme. This mainly
    // makes sense for skins provided by themes only.
    'status' => array(
      'bartik' => 1,
      'garland' => 0,
      // In case you are registering a skin for your base theme, then you likely
      // do not know which sub themes are going to use your base theme. By
      // setting the global default status to 0 (as above) and enabling the skin
      // for your base theme itself, the skin's status will be automatically
      // inherited to all sub themes of your base theme.
      'mybasetheme' => 1,
    ),
  );
  return $skins;
}

/**
 * Define one or more skins in an atomic Skinr plugin file.
 *
 * This hook works identically to hook_skinr_skin_info(), but allows to place
 * one or more related skin definitions into a separate plugin file.
 *
 * For example, considering a module or theme with the name "extension" that
 * contains an include file:
 * @code
 * extension/skins/example/example.inc
 * @encode
 * The "hook" prefix is substituted with the name of the module or theme
 * implementing it ("extension"), and PLUGIN is substituted with the name of the
 * include file ("example"), e.g., THEME_skinr_skin_PLUGIN_info() or
 * MODULE_skinr_skin_PLUGIN_info(). For above example, the function name would
 * be: extension_skinr_skin_example_info().
 */
function hook_skinr_skin_PLUGIN_info() {
  $skins['extension_example_menus'] = array(
    'title' => t('Example menu styles'),
    'type' => 'select',
    'group' => 'skinr_menus',
    'theme hooks' => array('block__menu', 'block__menu_block'),
    'attached' => array(
      'css' => array('css/nav.css'),
    ),
    'options' => array(
      'menu_a' => array(
        'title' => t('Standard (1 level) - Green'),
        'class' => array('nav', 'nav-a'),
        'attached' => array('css' => array('css/nav-colors.css')),
      ),
      'menu_b' => array(
        'title' => t('Standard (1 level) - Blue'),
        'class' => array('nav', 'nav-b'),
        'attached' => array('css' => array('css/nav-colors.css')),
      ),
    ),
  );
  return $skins;
}

/**
 * Perform alterations on Skinr skins.
 *
 * @param $skins
 *   An array of skin information exposed by hook_skinr_skin_info()
 *   implementations.
 */
function hook_skinr_skin_info_alter(&$skins) {
  // Remove restrictions on theme hooks the skin works with.
  unset($skins['skinr_menus']['theme hooks']);
}

/**
 * Defines group(s) that will contain skins.
 *
 * Groups are form element containers used to organize skins categorically. If
 * you do not define a group, your skins will appear in Skinr's default group,
 * which is labeled "General." Skinr implements 4 default groups, which may be
 * used in any skin implementation. For more information, see skins/default.inc.
 *
 * Each group name must be unique. It is recommended to prefix the name of each
 * group with the name of the theme or module name implementing it, followed by
 * the name of the group. Note that you cannot define 2 groups with the same
 * name, even if they are in different plugins.
 *
 * Group properties:
 * - title (required): Brief title of the tab.
 * - description (optional): Description of the group for administration page.
 * - weight (discouraged): Weight of the tab group; 0 by default.
 *
 * The "hook" prefix is substituted with the name of the module or theme that
 * implements it.
 *
 * @see skinr_default_skinr_group_info()
 */
function hook_skinr_group_info() {
  $group['skinr_menus'] = array(
    'title' => t('Menus'),
    'description' => t('Menu and navigation styles.'),
  );

  return $groups;
}

/**
 * Define one or more skin groups in an atomic Skinr plugin file.
 *
 * This hook works identically to hook_skinr_group_info(), but allows to place
 * one or more related skin group definitions into a separate plugin file.
 *
 * For example, considering a module or theme with the name "extension" that
 * contains an include file:
 * @code
 * extension/skins/example/example.inc
 * @encode
 * The "hook" prefix is substituted with the name of the module or theme
 * implementing it ("extension"), and PLUGIN is substituted with the name of the
 * include file ("example"), e.g., THEME_skinr_group_PLUGIN_info() or
 * MODULE_skinr_group_PLUGIN_info(). For above example, the function name would
 * be: extension_skinr_group_example_info().
 */
function hook_skinr_group_PLUGIN_info() {
  $group['extension_example_menus'] = array(
    'title' => t('Menus'),
    'description' => t('Menu and navigation styles.'),
  );
  return $groups;
}

/**
 * Perform alterations on Skinr groups.
 *
 * @param $groups
 *   An array of group information exposed by hook_skinr_group_info()
 *   implementations.
 */
function hook_skinr_group_info_alter(&$groups) {
  // Show this tab group at the top of the Skinr settings form.
  $groups['skinr_menus']['weight'] = -1;
}

/**
 * @}
 */
