<?php
/**
 * @file
 * Theme function for the pager.
 */

/**
 * Theme override for theme_pager().
 * @see theme_pager()
 */
function mediamosa_sb_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next ›')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

  $li_classes = array(array('prev pager-first'), array('pager-previous'), array(), array('pager-next'), array('pager-last next'));

  if (!$li_first) {
    $li_first = theme('pager_placeholder', array('text' => isset($tags[0]) ? $tags[0] : t('« first')));
    $li_classes[0][] = 'disabled prev';
  }
  if (!$li_last) {
    $li_last = theme('pager_placeholder', array('text' => isset($tags[4]) ? $tags[4] : t('last »')));
    $li_classes[4][] = 'disabled next';
  }
  if (!$li_previous) {
    $li_previous = theme('pager_placeholder', array('text' => isset($tags[1]) ? $tags[1] : t('‹ previous')));
    $li_classes[1][] = 'disabled' . ($li_first ? '' : ' prev');
  }
  if (!$li_next) {
    $li_next = theme('pager_placeholder', array('text' => isset($tags[3]) ? $tags[3] : t('next ›')));
    $li_classes[3][] = 'disabled' . ($li_last ? '' : ' next');
  }

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => $li_classes[0],
        'data' => $li_first,
      );
    }

    if ($li_previous) {
      $items[] = array(
        'class' => $li_classes[1],
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current active'),
            'data' => theme('pager_placeholder', array('text' => $i)),
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
    }

    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => $li_classes[3],
        'data' => $li_next,
      );
    }

    if ($li_last) {
      $items[] = array(
        'class' => $li_classes[4],
        'data' => $li_last,
      );
    }

    return '<div class="pagination"><h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
      'items' => array_filter($items),
    )) . '</div>';
  }
}

/**
 * Theme function for a pager placeholder.
 * @ingroup themeable.
 */
function mediamosa_sb_pager_placeholder($variables) {
  if (!$variables['text']) return '';
  return '<a disabled="disabled">' . $variables['text'] . '</a>';
}
