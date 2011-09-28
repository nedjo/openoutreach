Subprofiles
-----------

Subprofiles makes it possible to provide different flavours, called
subprofiles, of a given installation profile. Subprofiles are defined in the
profile's .info file, and consist of a set of features available for enabling,
with a default enable status. In an interactive install, the site configuration
form includes elements to select which subprofile to install and can further
specify exactly which of the subprofile's features to enable.

Developer instructions
----------------------

To add subprofiles support to your installation profile:

1. Edit the profile's .info file and make the following additions:
   * Add subprofiles as a dependency:
     <code>
     dependencies[] = subprofiles
     </code>
   * Add a section specifying the available subprofiles. A 'standard'
     subprofile is required and will be used if no subprofile is
     specified.
     <code>
     subprofiles[standard][name] = My Profile standard
     subprofiles[standard][description] = Install a full version of My Profile with all commonly needed features enabled.
     // A feature called feature_x that should be enabled by default.
     subprofiles[standard][features][feature_x] = TRUE
     subprofiles[standard][features][feature_y] = TRUE
     // A feature called feature_z that should be available but disabled by
     // default.
     subprofiles[standard][features][feature_z] = FALSE
     </code>

2. In your .profile file, or an include file loaded at install time, add an
   install task:
   <code>
    /**
     * Generate an install task to install subprofile features.
     *
     * @param $install_state
     *   An array of information about the current installation state.
     *
     * @return
     *   The install task definition.
     */
    function example_install_tasks($install_state) {
      if (module_exists('subprofiles')) {
        return _subprofiles_install_tasks($install_state);
      }
    }
   </code>

