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

An example site can be viewed at:

https://sitebuilder.mediamosa.surfnet.nl/


System Requirements
===================

The minimal requirements are:

Disk space: 15 Megabytes

SiteBuilder stores small caches of images on it's own site, so as the number of
assets increase, so will the required disk space.

MediaMosa 3.1 or higher. You will need a running MediaMosa installation,
version 3.1 and up is required.

Web server: Apache 1.3, Apache 2.x, nginx, or Microsoft IIS

Database server: MySQL (or MariaDB) 5.0.15 or higher with PDO.

PHP: Drupal 7: 5.2.5 or higher (5.3 recommended)

See http://drupal.org/requirements for more information on general
Drupal requirements.

MediaMosa 3.1 or higher. You will need a running MediaMosa
installation, version 3.1 and up is supported.


GIT instructions
================

Clone Sitebuilder as normal from github using any of the provided
url's, for example

$ git clone git://github.com/mediamosa/MediaMosa-SiteBuilder.git

Because SiteBuilder is depended on the correct version of SDK and CK, you need
to pull them using git-submodule;

$ git submodule init
$ git submodule update

When SiteBuilder is updated, make sure you not only do
$ git pull

but also

$ git submodule update

This will update any updates to the submodules. SiteBuilder will be released 
under a new version number when one of the submodules has been updated, even 
when SiteBuilder has not changed.


Installation
============

The Sitebuilder is packaged as a Drupal distribution. See
http://drupal.org/documentation/install for instructions how to install
Drupal.
