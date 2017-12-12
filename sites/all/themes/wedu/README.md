# Setting up.

######  __[ * ]  *Preffered*__


1. __First step__ : 
To place the theme, we have to be in the **_'MediaMosa: Sitebuilder'_** folder *(that you are using for your site)*.

2. __Second step__ :
  The theme has to be (ofcourse) in the **_'theme'_** folder, so drupal knows we have got a theme for him. Place the **_‘Wedu’_** folder into: *MediaMosa/sites/all/themes*

3. __*Third step**__   :
 This step fixes **errors** and the problem with showing **_no description_** of *media assets* at the bottom of the asset/detail/* page.  Place the **‘’mediamosa_sb_feature’’** folder into: *MediaMosa/Sites/all/modules/custom/*


4. __Final step__ : 
To **activate** the new theme, we have to select __appearance__ on the *webpage*. It can be found at the left side of the page, right in the *administration tab*. Now scroll down and look for **Wedu**, when you've found it click on *‘’enable and set default’’*



##Configuration.*
####This configuration is (*) preffered and  optional.

- Go to: __*Adminstration/ Structure/ Block*__ now find and place the following blocks to the right regions:

######Region | *Block*

###### __*Header*__ | *Search form*
  
###### __*Highlighted*__ | *View MediaMosa Asset Featured*
 
###### __*Content*__ | *View MediaMosa New* 
 
###### __*Content*__ | *View MediaMosa Asset Popular* 
 
###### __*Content*__ | *Main Page content* 
 
###### __*Content*__ | *View MediaMosa Assets*

> Final thing, click next to ‘View: MediaMosa Assets’ on configure and choose: ‘Only the listed pages’ ; and fill in: asset/detail/*
-The other two ‘’ View :‘’ blocks in Content should have  ‘’ Only the listed pages :  <front> ’’

