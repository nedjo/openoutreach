
## Setting up the Slideshow

1. Download and install the http://drupal.org/project/nodesinblock module.

2. Add an image style to suit the size of images you want in the slideshow:
   admin/config/media/image-styles.

   You image style must work so that all images will be the same size, and
   you know what that size is. For example set it to crop all images to 940x300px.
   The default settings for the theme are setup to use an image 940px wide, but
   you can choose whatever you want, just make a note of it because we need that
   width later on in step 8.

3. Add a content type called "Slideshow" (the machine name must be "slideshow").
   You can leave the body field or remove it if you want. If you leave it you
   should set it to "hidden" in the field display settings.

   Set up the content type with these setting:
   - Publishing option: Published
   - Display settings: dont display author and date info.
   - Comment settings: closed

4. Add an image field called "slide" to the new Slideshow content type.

   Configure it to allow unlimited values and enable the alt and title
   fields. The title field we will use for captions and the alt field is
   good for accessibility.

   Under field display settings configure the field to use the image style
   you set up in step 2.

5. Now we should configure the Nodes in Block module: admin/structure/nodesinblock

   1. General settings
      - Total number of blocks: 1 (you can try with more, I have only ever tested with 1)
      - Content types: Slideshow

   2. Settings per block
      - User friendly name for block 1: My Slideshow (or whatever you want to use)
      - Visibility settings for block 1: Show on only the listed pages

   3. Settings per content type
      - check the setting for "My Slideshow" (or whatever user friendly name you used in step 2)
      - uncheck "Collapsed fieldset" and "Collapsible fieldset"
      - set the Render Mode to: Full Content without links

6. Now create a Slideshow node.
   - add some images, use the title field if you want a caption on each field
   - find the Nodes in block vertical tab and set "Select region" to "My Slideshow (Pos)", and
     add the visibility setting you require for this node block. This is the key difference to
     normal blocks - you set the visiblity here on the node form, not in the normal block settings.

7. Go to the block settings, find the "My Slideshows" block and place it in a region, such as the
   "Featured" region.

8. Finally go to the theme settings page for AT Commerce. Find the vertical tab for "Slideshow".
   Make sure:
    - Enable slideshow javascript setting is checked
    - Enter the width of the image, what you setup in step 2 for the image style, e.g 940
    - Check or uncheck captions and controls as desired

    Save the theme settings. Celebrate a little, you did it!

    Now go and view your slideshow, it should be working. If not then review each step, a likely
    thing is to forget the setting on the node form. If you are really jammed and suspect there
    is a bug please post an issue: http://drupal.org/project/issues/at-commerce


## Theming the Slideshow

  AT Commerce comes with a CSS file called styles.slideshow.css - in here are most of the styles for
  the default styling. There is a small amount in at_commerce.responsive.style.css to re-position
  the directional navigation arrows when in small screens.

  You can modify these CSS files directly, or subtheme AT Commerce using Footheme:
  http://drupal.org/project/footheme




