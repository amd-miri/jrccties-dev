
collapse_text.module is an input filter to allow sections of text to be
made into collapsible sections (like on editing forms).

Surround a section of text with `[collapse]` and `[/collapse]` to make
that section collapsible. You may nest `[collapse]` tags within
other `[collapse]` tags.

Use the `[collapsed]` tag to make the section default to collapsed.
`[collapsed]` is the same thing as `[collapse collapsed]`, if you prefer
to use the longer form.

The title for the section may be specified in two ways:

- You may add a "title=" parameter to the opening tag, such as
  `[collapse title="your title here"]`. Titles should be surrounded
  by double-quotes. You can use HTML entities in titles, so use
  `&quot;` if you need to include them in your title.
- If a title is not specified in the `[collapse]` tag, the module will
  search forward until the next `[collapse]` or `[/collapse]` tag, and
  find the first HTML header (<h1>, <h2>, ..., <h6>) and use that for
  the title. This will be removed from the text to prevent duplication.

If a title is not specified, there is a default title that will be used.

You may also add a "class=" parameter to specify CSS classes to be added
to the section. These classes should be surrounded by double-quotes, and
separated by spaces: `[collapse class="class1 class2 class3"]`.

The parameters may be combined in (almost) any order. The "collapsed"
parameter must come right after the word "collapse". If you wish to
put the "collapsed" parameter anywhere else, you need to specify it as
`collapsed="collapsed"`:
    `[collapse title="title" collapsed="collapsed" class="class1"]`

If you need to actually have the string `[collapse` show up anywhere in
the text, you will need to escape the tag by prefixing it with a backslash:
    `\[collapse`
The first backslash before any instance of `[collapse` will be removed
from the final displayed text, so if you want to display `\[collapse`,
you should enter `\\[collapse`, and if you want to display `\\[collapse`,
you will need to type `\\\[collapse`, etc.

You may use angle brackets instead of straight brackets to surround the
collapse tag if you wish: `<collapse>` will be turned into `[collapse]`
and function the same.

For backwards compatibility, this module supports a few variations which
should not be used going forward. The "class=" parameter used to be
"style=". It used to be that the "style=" and "title=" parameters did
not require quotes. For this to work, the "style=" parameter must come
before the "title=" parameter.

There are two theme functions you can override if you need to.

- `theme_collapse_text_fieldset()` renders the actual fieldset.
- `theme_collapse_text_form()` renders the enclosing form.

N.B. The HTML corrector filter is known to cause collapsible text to
not function properly.  If you use HTML corrector, make sure that you
arrange your filters such that collapse text is below (heavier than)
HTML corrector.  You can find this setting in admin/settings/filters.
