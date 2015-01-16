<?php

/**
 * @see hook_entity_property_info()
 */
class RegistrationMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['registration_id'] = array(
      'label' => t("Registration ID"),
      'type' => 'integer',
      'description' => t("The unique ID of the registration."),
      'schema field' => 'registration_id',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['type'] = array(
      'label' => t("Registration type"),
      'type' => 'token',
      'description' => t("The type of the registration."),
      'options list' => 'registration_type_get_names',
      'required' => TRUE,
      'schema field' => 'type',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['entity_type'] = array(
      'label' => t("Host entity type"),
      'type' => 'token',
      'description' => t("The entity type of the host entity."),
      'required' => TRUE,
      'schema field' => 'entity_type',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['entity_id'] = array(
      'label' => t("Host entity ID"),
      'type' => 'integer',
      'description' => t("The entity ID of the host entity."),
      'required' => TRUE,
      'schema field' => 'entity_id',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['count'] = array(
      'label' => t("Slots consumed"),
      'type' => 'integer',
      'description' => t("How many slots the registration consumes from the host entity."),
      'schema field' => 'count',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['created'] = array(
      'label' => t("Date created"),
      'type' => 'date',
      'schema field' => 'created',
      'description' => t("The date the registration was created."),
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['updated'] = array(
      'label' => t("Date updated"),
      'type' => 'date',
      'schema field' => 'updated',
      'description' => t("The date the registration was most recently updated."),
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['anon_mail'] = array(
      'label' => t('Anonymous e-mail'),
      'type' => 'text',
      'schema field' => 'anon_mail',
      'description' => t('An e-mail address associated with the registration of an anonymous user.'),
      'getter callback' => 'registration_get_properties',
      'setter callback' => 'registration_property_email_set',
    );

    // Provides a single calculated property that contains either the associated user's email address or the
    // anonymous email used if no user is associated with the registration
    $properties['mail'] = array(
      'label' => t('Registrant e-mail'),
      'type' => 'text',
      'description' => t('Either the user email address, if registration is for a user, or the anonymous user email property.'),
      'getter callback' => 'registration_get_properties',
      'computed' => TRUE,
    );

    // Entities
    $properties['entity'] = array(
      'label' => t("Host entity"),
      'type' => 'entity',
      'schema field' => 'entity',
      'description' => t("The host entity."),
      'getter callback' => 'registration_property_host_get',
      'setter callback' => 'registration_property_host_set',
    );

    $properties['author'] = array(
      'label' => t("Author entity"),
      'type' => 'user',
      'schema field' => 'author_uid',
      'description' => t("The user who created the registration."),
      'getter callback' => 'registration_property_author_get',
      'setter callback' => 'entity_property_verbatim_set',
    );

    $properties['user'] = array(
      'label' => t("User entity"),
      'type' => 'entity',
      'schema field' => 'user_uid',
      'description' => t("The entity for which the registration belongs to. Usually a user."),
      'getter callback' => 'registration_property_user_get',
      'setter callback' => 'registration_property_user_set',
    );

    $properties['state'] = array(
      'label' => t("State entity"),
      'type' => 'registration_state',
      'schema field' => 'state',
      'options list' => 'registration_get_states_options',
      'description' => t("The state of the registration."),
      'setter callback' => 'entity_property_verbatim_set',
    );
    return $info;
  }

}
