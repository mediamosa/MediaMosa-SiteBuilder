MediaMosa Sitebuilder
=====================

The Sitebuilder is a Drupal distribution for a example media site
connected to MediaMosa. Some features:
- upload media,
- play media,
- show lists of media,
- transcode videos,
- add restrictions to media,
- metadata,
- many more.

all in a nice interface. An example site can be viewed at:

https://sitebuilder.mediamosa.surfnet.nl/

GIT instructions
================

Clone Sitebuilder as normal from github using any of the provided
url's, for example

$ git clone https://github.com/mediamosa/MediaMosa-SiteBuilder.git

Sitebuilder uses 2 submodules (MediaMosa SDK and CK), you must include
them to get it working:

$ cd mediamosa_sb/
$ git submodule init
$ git submodule update

Sitebuilder will not work without the submodules.


System Requirements
===================

The minimal requirements are:

Disk space: 15 Megabytes

  The sitebuilder stores small caches of images on it's own site, so
  as the number of assets increase, so will the required disk space.

Web server: Apache 1.3, Apache 2.x, or Microsoft IIS

Database server: MySQL (or MariaDB) 5.0.15 or higher with PDO.

PHP: Drupal 7: 5.2.5 or higher (5.3 recommended)

See http://drupal.org/requirements for more information on general
Drupal requirements.

MediaMosa 3.1 or higher. You will need a running MediaMosa
installation, version 3.1 and up is supported.


Installation
============

The Sitebuilder is packaged as a Drupal distribution. See
http://drupal.org/documentation/install for instructions how to install
Drupal.


