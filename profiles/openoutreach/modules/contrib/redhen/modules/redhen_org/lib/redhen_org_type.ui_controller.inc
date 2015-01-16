<?php

/**
 * Redhen Contact Type UI controller.
 */
class RedhenOrgTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage organization entity types, including adding and removing fields and the display of fields.';
    return $items;
  }

  /**
   * Override parent::operationForm to set a more meaningful message on delete.
   */
  public function operationForm($form, &$form_state, $entity, $op) {
    switch ($op) {
      case 'delete':
        $query = new EntityFieldQuery();
        $count = $query
          ->entityCondition('entity_type', 'redhen_org')
          ->entityCondition('bundle', $entity->name)
          ->count()
          ->execute();

        $label = entity_label($this->entityType, $entity);
        $confirm_question = t('Are you sure you want to delete the %entity %label?', array('%entity' => $this->entityInfo['label'], '%label' => $label));
        $form['delete_entities'] = array(
          '#type' => 'checkbox',
          '#title' => t('If checked, all %count organizations of type %type will also be deleted.', array('%type' => $label, '%count' => $count)),
          '#description' => t('If you have a large number of organizations of type %type, this may cause a timeout. Use with caution.', array('%type' => $label)),
          '#access' => ($count > 0),
          '#default_value' => FALSE,
        );
        $desc = t('Click confirm to delete the organization type %label. This operation cannot be undone.', array('%label' => $label));
        return confirm_form($form, $confirm_question, $this->path, $desc);

      default:
        return parent::operationForm($form, $form_state, $entity, $op);
    }
  }

  /**
   * Override parent to pass our delete entities flag in the delete op.
   */
  public function operationFormSubmit($form, &$form_state) {
    if ($form_state['op'] == 'delete') {
      $entity = $form_state[$this->entityType];
      $delete_entities = $form_state['values']['delete_entities'];
      $entity->delete($delete_entities);
      $label = entity_label($this->entityType, $entity);
      $msg = t('Successfully deleted organization type %label.', array('%label' => $label));
      if ($delete_entities) {
        $msg = t('Successfully deleted organization type %label and all %label organizations.', array('%label' => $label));
      }
      drupal_set_message($msg);
      $form_state['redirect'] = $this->path;
    }
    else {
      parent::operationFormSubmit($form, $form_state);
    }
  }

}
