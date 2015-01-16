<?php // AT Commerce ?>
<div id="page-wrapper">
  <div id="page" class="<?php print $classes; ?>">

    <?php if($page['draw']): ?>
      <div id="draw-wrapper">
        <div class="container clearfix">
          <div id="draw"><?php print render($page['draw']); ?></div>
        </div>
      </div>
    <?php endif; ?>

    <div id="header-wrapper">
      <?php if($page['draw']): ?>
        <div id="toggle-wrapper">
          <div class="container clearfix">
             <div id="toggle"><?php print $draw_link; ?></div>
          </div>
        </div>
      <?php endif; ?>

      <div class="container clearfix">
        <header class="clearfix">

          <?php if ($site_logo || $site_name || $site_slogan): ?>
            <!-- start: Branding -->
            <div id="branding" class="branding-elements clearfix<?php print $branding_classes ? ' ' . $branding_classes : ''; ?>">

              <?php if ($site_logo): ?>
                <div id="logo">
                  <?php print $site_logo; ?>
                </div>
              <?php endif; ?>

              <?php if ($site_name || $site_slogan): ?>
                <!-- start: Site name and Slogan hgroup -->
                <div id="name-and-slogan"<?php print $hgroup_attributes; ?>>

                  <?php if ($site_name): ?>
                    <h1 id="site-name"<?php print $site_name_attributes; ?>><?php print $site_name; ?></h1>
                  <?php endif; ?>

                  <?php if ($site_slogan): ?>
                    <h2 id="site-slogan"<?php print $site_slogan_attributes; ?>><?php print $site_slogan; ?></h2>
                  <?php endif; ?>

                </div><!-- /end #name-and-slogan -->
              <?php endif; ?>


            </div><!-- /end #branding -->
          <?php endif; ?>

          <?php print render($page['header']); ?>

          <?php if ($page['menu_bar']): ?>
            <div id="menu-wrapper"><?php print render($page['menu_bar']); ?></div>
          <?php endif; ?>

        </header>
      </div>
    </div>

    <?php if ($page['secondary_content']): ?>
      <div id="secondary-content-wrapper">
        <div class="texture-overlay">
          <div class="container clearfix">
            <?php print render($page['secondary_content']); ?>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <div id="content-wrapper" class="<?php print $page['secondary_content'] ? 'with-secondary' : 'no-secondary'; ?>"><div class="container">

      <?php if (
          $page['three_33_top'] ||
          $page['three_33_first'] ||
          $page['three_33_second'] ||
          $page['three_33_third'] ||
          $page['three_33_bottom']
          ): ?>
        <div id="sub-panels-wrapper">
          <!-- Three column 3x33 Gpanel -->
          <div class="at-panel gpanel panel-display three-3x33 clearfix">
            <?php print render($page['three_33_top']); ?>
            <?php print render($page['three_33_first']); ?>
            <?php print render($page['three_33_second']); ?>
            <?php print render($page['three_33_third']); ?>
            <?php print render($page['three_33_bottom']); ?>
          </div>
        </div>
      <?php endif; ?>

      <?php if ($messages || $page['help']): ?>
        <div id="messages-help-wrapper" class="clearfix">
          <?php print $messages; ?>
          <?php print render($page['help']); ?>
        </div>
      <?php endif; ?>

      <?php if ($breadcrumb): ?>
        <section id="breadcrumb" class="clearfix">
          <?php print $breadcrumb; ?>
        </section>
      <?php endif; ?>

      <div id="columns">
        <div class="columns-inner clearfix">

          <div id="content-column">
            <div class="content-inner">

              <?php print render($page['highlighted']); ?>

              <?php if (
                $page['two_50_top'] ||
                $page['two_50_first'] ||
                $page['two_50_second'] ||
                $page['two_50_bottom']
                ): ?>
                <!-- Two column 2x50 -->
                <div class="at-panel gpanel panel-display two-50 clearfix">
                  <?php print render($page['two_50_top']); ?>
                  <?php print render($page['two_50_first']); ?>
                  <?php print render($page['two_50_second']); ?>
                  <?php print render($page['two_50_bottom']); ?>
                </div>
              <?php endif; ?>

              <<?php print $tag; ?> id="main-content">

                <?php print render($title_prefix); ?>
                <?php if ($title && !isset($node)): ?>
                  <header>
                    <h1 id="page-title"><?php print $title; ?></h1>
                  </header>
                <?php endif; ?>
                <?php print render($title_suffix); ?>

                <?php if ($primary_local_tasks || $secondary_local_tasks || $action_links): ?>
                  <div id="tasks">

                    <?php if ($primary_local_tasks): ?>
                      <ul class="tabs primary clearfix"><?php print render($primary_local_tasks); ?></ul>
                    <?php endif; ?>

                    <?php if ($secondary_local_tasks): ?>
                      <ul class="tabs secondary clearfix"><?php print render($secondary_local_tasks); ?></ul>
                    <?php endif; ?>

                    <?php if ($action_links = render($action_links)): ?>
                      <ul class="action-links clearfix"><?php print $action_links; ?></ul>
                    <?php endif; ?>

                  </div>
                <?php endif; ?>

                <?php if ($content = render($page['content'])): ?>
                  <div id="content">
                    <?php print $content; ?>
                  </div>
                <?php endif; ?>

              </<?php print $tag; ?>>

              <?php print render($page['content_aside']); ?>

            </div>
          </div>

          <?php print render($page['sidebar_first']); ?>
          <?php print render($page['sidebar_second']); ?>

        </div>
      </div>

      <?php if ($page['tertiary_content']): ?>
        <div id="tertiary-content-wrapper">
          <?php print render($page['tertiary_content']); ?>
        </div>
      <?php endif; ?>

      </div>
    </div>

    <?php if (
      $page['five_first'] ||
      $page['five_second'] ||
      $page['five_third'] ||
      $page['five_fourth'] ||
      $page['five_fifth']
      ): ?>
      <!-- Five column Gpanel -->
      <div id="quint-panels-wrapper">
        <div class="texture-overlay">
          <div class="container clearfix">
            <div class="at-panel gpanel panel-display five-5x20 clearfix">
              <div class="panel-row row-1 clearfix">
                <?php print render($page['five_first']); ?>
                <?php print render($page['five_second']); ?>
              </div>
              <div class="panel-row row-2 clearfix">
                <?php print render($page['five_third']); ?>
                <?php print render($page['five_fourth']); ?>
                <?php print render($page['five_fifth']); ?>
              </div>
            </div>
          </div>
        </div>
      </div>
    <?php endif; ?>

    <div id="page-footer">
      <?php if (
        $page['four_first'] ||
        $page['four_second'] ||
        $page['four_third'] ||
        $page['four_fourth']
        ): ?>
        <!-- Four column Gpanel -->
        <div id="footer-panels-wrapper">
          <div class="container clearfix">
            <div class="at-panel gpanel panel-display four-4x25 clearfix">
              <div class="panel-row row-1 clearfix">
                <?php print render($page['four_first']); ?>
                <?php print render($page['four_second']); ?>
              </div>
              <div class="panel-row row-2 clearfix">
                <?php print render($page['four_third']); ?>
                <?php print render($page['four_fourth']); ?>
              </div>
            </div>
          </div>
        </div>
      <?php endif; ?>

      <?php if ($page['footer'] || $attribution): ?>
        <div id="footer-wrapper">
          <div class="container clearfix">
            <footer class="clearfix">
              <?php print render($page['footer']); ?>
              <?php print $attribution; ?>
            </footer>
         </div>
      </div>
      <?php endif; ?>
    </div>

  </div>
</div>
