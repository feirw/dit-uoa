# -*- coding: utf-8 -*-
import os
import re

BASE = r"C:\Users\elenz\OneDrive - Threenitas\Desktop\sxbd"
SKIP_HTML = {"_sxbd_materials_snippet.html"}


def is_broken(page_path, href):
    if href.startswith(("http", "css/", "js/")):
        return False
    if href.endswith(".html"):
        return False
    target = os.path.normpath(os.path.join(os.path.dirname(page_path), href))
    return not os.path.exists(target)


def audit():
    missing_by_page = {}
    for root, dirs, files in os.walk(BASE):
        dirs[:] = [d for d in dirs if d not in {".git", ".tools", "css", "js", "__pycache__"}]
        for fn in files:
            if not fn.endswith(".html") or fn.startswith("_") or fn in SKIP_HTML:
                continue
            path = os.path.join(root, fn)
            rel = os.path.relpath(path, BASE)
            text = open(path, encoding="utf-8").read()
            for m in re.finditer(r'href="([^"#]+)"', text):
                href = m.group(1)
                if is_broken(path, href):
                    missing_by_page.setdefault(rel, []).append(href)
    return missing_by_page


def remove_file_cards(html, broken_hrefs):
    broken = set(broken_hrefs)
    pattern = re.compile(
        r'(\s*)<a href="([^"]+)" target="_blank" class="file-card">.*?</a>',
        re.DOTALL,
    )

    def repl(m):
        indent, href = m.group(1), m.group(2)
        return "" if href in broken else m.group(0)

    html = pattern.sub(repl, html)

    # remove empty categories
    html = re.sub(
        r'\n    <div class="materials-category">\n        <h3>[^<]+</h3>\n        <div class="file-list">\n        </div>\n    </div>',
        "",
        html,
    )
    html = re.sub(
        r'\n    <div class="materials-category">\n        <h3>[^<]+</h3>\n        <div class="file-list">\s*\n        </div>\n    </div>',
        "",
        html,
    )
    return html


if __name__ == "__main__":
    missing = audit()
    total = sum(len(v) for v in missing.values())
    print(f"pages with broken links: {len(missing)}, total links: {total}")
    for page in sorted(missing):
        print(f"  {page}: {len(missing[page])}")

    for page, hrefs in sorted(missing.items()):
        path = os.path.join(BASE, page)
        html = open(path, encoding="utf-8").read()
        new_html = remove_file_cards(html, hrefs)
        if new_html != html:
            open(path, "w", encoding="utf-8", newline="\n").write(new_html)
            print(f"updated {page}")

    missing2 = audit()
    print(f"after fix: {sum(len(v) for v in missing2.values())} broken links")
