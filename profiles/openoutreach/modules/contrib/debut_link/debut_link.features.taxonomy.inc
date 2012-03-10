<?php
/**
 * @file
 * debut_link.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function debut_link_taxonomy_default_vocabularies() {
  return array(
    'link_terms' => array(
      'name' => 'Link terms',
      'machine_name' => 'link_terms',
      'description' => 'For use in classifying resource links.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'metatags' => array(),
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
