// $Id: context_layouts_reaction_block.js,v 1.1.2.1.2.1 2010/09/17 18:40:26 yhahn Exp $

(function($) {

Drupal.behaviors.contextLayoutsReactionBlock = {};
Drupal.behaviors.contextLayoutsReactionBlock.attach = function(context) {
  // ContextBlockForm: Init.
  $('.context-blockform-layout:not(.contextLayoutsProcessed)').each(function() {
    $(this).addClass('contextLayoutsProcessed');
    $(this).change(function() {
      var layout = $(this).val();
      if (Drupal.settings.contextLayouts.layouts[layout]) {
        $('#context-blockform td.blocks table').hide();
        $('#context-blockform td.blocks div.label').hide();
        for (var key in Drupal.settings.contextLayouts.layouts[layout]) {
          var region = Drupal.settings.contextLayouts.layouts[layout][key];
          $('.context-blockform-regionlabel-'+region).show();
          $('#context-blockform-region-'+region).show();
        }
        if (Drupal.contextBlockForm) {
          Drupal.contextBlockForm.setState();
        }
      }
    });
    $(this).change();
  });
};

})(jQuery);