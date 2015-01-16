# RedHen Engagement

## Description

"Engagement scoring" (often referred to as "engagement analytics" or "engagement metrics") is a relatively new concept in measuring the interactions of web site visitors. Web analytics packages such as Google Analytics generally focus on measuring *quantitative* analytics - or the number of page visits and clicks. Engagement scoring focuses on measuring the *quality* of these interactions by weighting the value of different types of interactions between site visitors and your website. For example, sharing an article from your website to a social network might be worth "5 engagement points", commenting on a blog post might be worth "10 points."

The RedHen Engagement module provides an API and framework for tracking this type of engagement. The module also integrates with the "RedHen Notes" module, so that offline interactions with RedHen Contacts can also be tracked and scored.

## Configuration

* To create/manage engagement score bundles, go to: Structure > RedHen > Engagement Scores (http://yoursite.com/admin/structure/redhen/engagement_scores).
* For each engagement score bundle, set the point value of the type of engagement.

## Usage

* At the time of this writing, the RedHen Engagement module only provides an API for scoring site visitor's interactions with your website.
* However, you can *score* offline interactions with Contacts when when creating/editing RedHen Notes. At the bottom of the note add/edit screen, select an engagement score for a particular note.
* The total value of engagement scores for a Contact can be viewed from the main Contact Entity display.