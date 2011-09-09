<?php

/**
 * @file
 * Holds the contents of a preprocess function moved into its own file
 * to ease memory requirements and having too much code in one file.
 */

function _advanced_forum_preprocess_comment(&$variables) {
  /* Easy links to the comment and parent node */
  $comment = $variables['comment'];
  $node = node_load($comment->nid);
  $variables['first_post'] = $node;

  // This is a comment, not the node.
  $variables['top_post'] = FALSE;

  /* Determine the template file to use for the comment. */
  if (arg(1) == 'reply' || arg(1) == 'edit') {
    // Use the preview version
    advanced_forum_add_template_suggestions("post-preview", $variables);
  }
  else {
    // Use our combined node/comment template file
    advanced_forum_add_template_suggestions("post", $variables);
  }


  // Add in our classes overwriting existing.
  $variables['classes_array'] = array();
  $variables['classes_array'][] = 'forum-post clearfix';

  // Add the current language to the classes for image handling.
  global $language;
  if (!empty($language->language)) {
    $variables['classes_array'][] = $language->language;
  }

  // Add the poster's UID
  $variables['classes_array'][] = "posted-by-$comment->uid";

  // Add class if the poster is the viewer.
  global $user;
  if ($user->uid > 0 && $user->uid == $comment->uid) {
    $variables['classes_array'][] = "post-by-viewer";
  }

  // Add class if the poster is the topic starter.
  if ($node->uid > 0 && $node->uid == $comment->uid) {
    $variables['classes_array'][] = "post-by-starter";
  }

  // Set the post ID for theming / targetting
  $variables['post_id'] = "post-$comment->cid";

  /* Linked post number */
  if (!isset($post_number)) {
    static $post_number = 1;
  }

  $num_comments = $node->comment_count;
  $posts_per_page = variable_get('comment_default_per_page_' . $node->type, 50);

  $page_number = !empty($_GET['page']) ? $_GET['page'] : 0;

  // page_number sanity check
  if ($page_number > floor($num_comments / $posts_per_page))
    $page_number = floor($num_comments / $posts_per_page);

  if (!$page_number) {
    $page_number = 0;
  }

  $post_number++;

  $linktext = '#' . (($page_number * $posts_per_page) + $post_number);

  // Permalink
  //  You can erase next 3 lines if you wish to use built-in Permalink.
  //  Template adjusted: $post_link -> $permalink
  $uri = entity_uri('comment', $comment);
  $uri['options'] += array('attributes' => array('class' => 'permalink', 'rel' => 'bookmark'));
  $variables['permalink'] = l($linktext, $uri['path'], $uri['options']);

  /* In reply to */
  $variables['in_reply_to'] = "";
  if ($comment->pid > 0) {
    // Find the display position of the parent post;.
    $post_position = advanced_forum_post_position($node->nid, $comment->pid);

    // This extra if test is a sanity check in case the comment being replied
    // to no longer exists.
    if ($post_position > 0) {
      // Find the page the post is on. We need to compensate for the topic node
      // being #1 which puts an extra post on the first page but not on the rest.
      $page_number = floor(($post_position - 2) / $posts_per_page);

      // Assemble the link.
      $fragment = 'comment-' . $comment->pid;

      if ($page_number)
        $query = array('page' => $page_number);

      $linktext = t("(Reply to #!post_position)", array('!post_position' => $post_position));
      $linkpath = "node/$node->nid";
      $variables['in_reply_to'] = l($linktext, $linkpath, array('query' => empty($query) ? array() : $query, 'fragment' => $fragment));
    }
  }

  /* Title */
  if (variable_get('comment_subject_field_' . $node->type, 1) == 0) {
    // if comment titles are disabled, don't display it.
    $variables['title'] = '';
  }
  else {
    // Assign the subject to the title variable for consistancy with nodes.
    $variables['title'] = check_plain($comment->subject);
  }

  /* User information / author pane */
  if ($comment->uid == 0) {
    // Anonymous user. Make a fake user object for theme_username
    $variables['account']->name = empty($comment->name) ? "" : $comment->name;
    $variables['account']->homepage = empty($comment->homepage) ? "" : $comment->homepage;
    $variables['account']->email = empty($comment->email) ? "" : $comment->email;
  }
  else {
    // Load up the real user object
    $variables['account'] = user_load($comment->uid);
  }

  // Create the author pane
  if (module_exists('author_pane')) {
    $variables['author_pane'] = theme('author_pane', array(
      'account' => $variables['account'],
      'caller' => 'advanced_forum',
      'picture_preset' => variable_get('advanced_forum_user_picture_preset', ''),
      'context' => $comment,
      'disable_css' => TRUE
    ));
  }
  else {
    $variables['author_pane'] = theme('advanced_forum_simple_author_pane', array('context' => $comment));
  }
  /* Content */
  // Helpful $content variable for templates.
  foreach (element_children($variables['elements']) as $key) {
    // Adjust content vriable to suit post template
    if ($key == 'comment_body')
      $variables['content']['body'] = $variables['elements'][$key];
    else
      $variables['content'][$key] = $variables['elements'][$key];
  }

  /* Signatures */
  // Load the signature.
  if (module_exists('signature_forum')) {
    // If Signature For Forums is installed, use that
    $variables['signature'] = signature_forum_get_signature($comment);
  }
  elseif (variable_get('user_signatures', 0)) {
    if (!empty($variables['account']->signature)) {
      // Otherwise load Drupal's built in one, if enabled.
      $variables['signature'] = check_markup($variables['account']->signature, $variables['account']->signature_format, FALSE);
    }
  }

  // Adjust comment timestamp to match node template
  $variables['date'] = $variables['created'];

  /* Post edited */
  $variables['post_edited'] = (isset($variables['comment_edited'])) ? $variables['comment_edited'] : "";
}