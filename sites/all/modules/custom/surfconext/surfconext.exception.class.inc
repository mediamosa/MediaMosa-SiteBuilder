<?php
/**
 * MediaMosa is a Full Featured, Webservice Oriented Media Management and
 * Distribution platform (http://mediamosa.org)
 *
 * Copyright (C) 2012 SURFnet BV (http://www.surfnet.nl)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, you can find it at:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 */

/**
 * @file
 * The SURFconext exception class.
 */
class surfconext_exception extends Exception {

  const SEVERITY_HIGH = 80;
  const SEVERITY_NORMAL = 50;
  const SEVERITY_LOW = 20;

  public function __construct($msg = '', $severity = self::MEDIAMOSA_EXCEPTION_SEVERITY_NORMAL, $log = TRUE) {
    $msg = empty($msg) ? 'SURFconext exception was thrown.' : $msg;

    if ($severity >= SEVERITY_NORMAL || mediamosa_debug::is_debug()) {
      $log_serverity = $severity >= SEVERITY_HIGH ? WATCHDOG_CRITICAL : WATCHDOG_NOTICE;

      $levels = watchdog_severity_levels();

      // Get backtrace when you can.
      $backtrace = $this->getTraceAsString();

      if ($log) {
        mediamosa_watchdog::log(
          '@message (Exception thrown (severity: @severity) on line @line, in @file)<br />Partial backtrace: <pre>@backtrace</pre>',
          array(
            '@severity' => $levels[$log_serverity],
            '@message' => $msg,
            '@line' => $this->getLine(),
            '@file' => $this->getFile(),
            '@backtrace' => empty($backtrace) ? 'no backtrace available' : $backtrace,
          ),
          $log_serverity
        );
      }
    }

    parent::__construct($msg);
  }
}
