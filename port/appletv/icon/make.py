#!/usr/bin/env python3
"""Draws the Apple TV app icon and top shelf images into port/appletv/Assets.xcassets.

Original artwork, split into tvOS parallax layers: Back (sky over the sea, the horizon's glow, scanlines), Middle (a glowing
faceted crystal and its rays) and Front (the wordmark). A palette from PALETTES (PALETTE=name,
default sky). Needs rsvg-convert, ImageMagick and the Noto Sans font (Black Italic).

    PALETTE=sky port/appletv/icon/make.py
"""
import json, os, shutil, subprocess, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
XC = os.path.join(HERE, "..", "Assets.xcassets")
BRAND = os.path.join(XC, "App Icon & Top Shelf Image.brandassets")
# sky top, sky at the horizon, sea at the horizon, sea bottom, crystal light, crystal dark,
# crystal glow, wordmark, small title, outline
PALETTES = {
    "sky":    ("#1D6FD8", "#9FDCFF", "#1C6FB8", "#06264D", "#E9FBFF", "#2FB7F0", "#7FE3FF",
               "#FFFFFF", "#FFD34D", "#0A2346"),
    "sunset": ("#3B2A78", "#FF9E5E", "#B4475A", "#2A1030", "#FFF4DA", "#FF7A59", "#FFC27A",
               "#FFFFFF", "#FFE08A", "#2A0F2E"),
    "ruin":   ("#0E2A2E", "#4FA89A", "#164B4E", "#05181B", "#EFFFF8", "#3FD6A4", "#7DFFD0",
               "#F4FFF9", "#FFD34D", "#04161A"),
}
PALETTE = os.environ.get("PALETTE", "sky")
SKY_TOP, SKY_LOW, SEA_HI, SEA_LOW, CRY_LIGHT, CRY_DARK, GLOW, INK, TITLE, LINE = PALETTES[PALETTE]
FONT = "Noto Sans"
INFO = {"author": "xcode", "version": 1}
HORIZON = 0.66  # the sea starts this far down


def svg(w, h, body):
    return f'<svg xmlns="http://www.w3.org/2000/svg" width="{w}" height="{h}" viewBox="0 0 {w} {h}">{body}</svg>'


def back_body(w, h, sun_x=0.5):
    y = h * HORIZON
    lines = "".join(f'<rect x="0" y="{i * h / 120:.2f}" width="{w}" height="{h / 240:.2f}" fill="#000" '
                    f'opacity="0.06"/>' for i in range(120))
    # Low clouds: soft ellipses along the horizon.
    clouds = "".join(
        f'<ellipse cx="{w * cx:.1f}" cy="{y - h * dy:.1f}" rx="{w * rx:.1f}" ry="{h * ry:.1f}" '
        f'fill="#FFFFFF" opacity="{op}"/>'
        for cx, dy, rx, ry, op in ((0.12, 0.05, 0.16, 0.035, 0.35), (0.30, 0.09, 0.12, 0.03, 0.25),
                                   (0.78, 0.06, 0.18, 0.04, 0.35), (0.95, 0.11, 0.10, 0.025, 0.22)))
    # Glints on the water.
    glints = "".join(
        f'<rect x="{w * (sun_x + dx) - w * ln / 2:.1f}" y="{y + h * dy:.1f}" width="{w * ln:.1f}" '
        f'height="{h * 0.006:.1f}" rx="{h * 0.003:.1f}" fill="#FFFFFF" opacity="{op}"/>'
        for dx, dy, ln, op in ((0, 0.03, 0.22, 0.5), (-0.03, 0.07, 0.15, 0.35), (0.04, 0.12, 0.10, 0.25),
                               (-0.01, 0.18, 0.06, 0.18)))
    return f'''
      <defs>
        <linearGradient id="sky" x1="0" y1="0" x2="0" y2="1">
          <stop offset="0" stop-color="{SKY_TOP}"/><stop offset="1" stop-color="{SKY_LOW}"/></linearGradient>
        <linearGradient id="sea" x1="0" y1="0" x2="0" y2="1">
          <stop offset="0" stop-color="{SEA_HI}"/><stop offset="1" stop-color="{SEA_LOW}"/></linearGradient>
        <radialGradient id="sun" cx="{sun_x}" cy="{HORIZON}" r="0.45">
          <stop offset="0" stop-color="#FFFFFF" stop-opacity="0.85"/>
          <stop offset="0.25" stop-color="{SKY_LOW}" stop-opacity="0.5"/>
          <stop offset="1" stop-color="{SKY_LOW}" stop-opacity="0"/></radialGradient>
      </defs>
      <rect width="{w}" height="{y:.1f}" fill="url(#sky)"/>
      <rect y="{y:.1f}" width="{w}" height="{h - y:.1f}" fill="url(#sea)"/>
      {clouds}
      <rect width="{w}" height="{h}" fill="url(#sun)"/>
      <rect y="{y - h * 0.003:.1f}" width="{w}" height="{h * 0.006:.1f}" fill="#FFFFFF" opacity="0.7"/>
      {glints}{lines}'''


def back(w, h):
    return svg(w, h, back_body(w, h))


def crystal(cx, cy, s, rays=True):
    """A faceted crystal (an elongated octahedron seen from the side) at (cx, cy), half-height s."""
    t, b, l, r = (cx, cy - s), (cx, cy + s * 1.05), (cx - s * 0.52, cy - s * 0.12), (cx + s * 0.52, cy - s * 0.12)
    m = (cx + s * 0.08, cy - s * 0.02)  # the near facet's corner
    pts = lambda *p: " ".join(f"{x:.1f},{y:.1f}" for x, y in p)
    out = f'''
      <defs><radialGradient id="glow"><stop offset="0" stop-color="{GLOW}" stop-opacity="0.9"/>
        <stop offset="0.35" stop-color="{GLOW}" stop-opacity="0.35"/>
        <stop offset="1" stop-color="{GLOW}" stop-opacity="0"/></radialGradient></defs>
      <circle cx="{cx}" cy="{cy}" r="{s * 1.9:.1f}" fill="url(#glow)"/>'''
    if rays:
        for i in range(12):
            import math
            a = i * math.pi / 6 + 0.13
            x1, y1 = cx + math.cos(a) * s * 0.9, cy + math.sin(a) * s * 0.9
            x2, y2 = cx + math.cos(a) * s * 2.3, cy + math.sin(a) * s * 2.3
            out += (f'<line x1="{x1:.1f}" y1="{y1:.1f}" x2="{x2:.1f}" y2="{y2:.1f}" stroke="{GLOW}" '
                    f'stroke-width="{s * (0.05 if i % 2 else 0.09):.1f}" stroke-linecap="round" opacity="0.45"/>')
    out += f'''
      <polygon points="{pts(t, r, b, l)}" fill="{CRY_DARK}"/>
      <polygon points="{pts(t, m, l)}" fill="{CRY_LIGHT}"/>
      <polygon points="{pts(t, r, m)}" fill="{GLOW}"/>
      <polygon points="{pts(l, m, b)}" fill="{GLOW}" opacity="0.85"/>
      <polygon points="{pts(m, r, b)}" fill="{CRY_DARK}" opacity="0.9"/>
      <polygon points="{pts(t, r, b, l)}" fill="none" stroke="#FFFFFF" stroke-width="{s * 0.035:.1f}"
               stroke-linejoin="round" opacity="0.9"/>
      <circle cx="{cx - s * 0.14:.1f}" cy="{cy - s * 0.48:.1f}" r="{s * 0.07:.1f}" fill="#FFFFFF"/>'''
    return out


def middle(w, h):
    return svg(w, h, crystal(w * 0.5, h * 0.42, h * 0.27))


def wordmark(x, y, size, anchor="middle"):
    """'MEGA MAN' over 'LEGENDS', baseline of LEGENDS at y."""
    stroke = size * 0.07
    small = size * 0.30
    return f'''
      <text x="{x:.1f}" y="{y - size * 0.86:.1f}" text-anchor="{anchor}" font-family="{FONT}"
            font-weight="900" font-style="italic" font-size="{small:.1f}" letter-spacing="{small * 0.18:.1f}"
            fill="{TITLE}" stroke="{LINE}" stroke-width="{stroke * 0.6:.1f}" paint-order="stroke">MEGA MAN</text>
      <text x="{x + size * 0.03:.1f}" y="{y + size * 0.05:.1f}" text-anchor="{anchor}" font-family="{FONT}"
            font-weight="900" font-style="italic" font-size="{size:.1f}" letter-spacing="{-size * 0.02:.1f}"
            fill="{LINE}" opacity="0.55">LEGENDS</text>
      <text x="{x:.1f}" y="{y:.1f}" text-anchor="{anchor}" font-family="{FONT}" font-weight="900"
            font-style="italic" font-size="{size:.1f}" letter-spacing="{-size * 0.02:.1f}" fill="{INK}"
            stroke="{LINE}" stroke-width="{stroke:.1f}" paint-order="stroke">LEGENDS</text>'''


def front(w, h):
    return svg(w, h, wordmark(w * 0.5, h * 0.80, h * 0.30))


def shelf(w, h):
    # One flat image, the art right of centre and the wordmark left, clear of the system's row of
    # apps over the bottom.
    s = h / 720
    body = back_body(w, h, sun_x=0.72)
    body += crystal(w * 0.72, h * 0.40, 190 * s)
    body += wordmark(w * 0.36, h * 0.55, 190 * s)
    return svg(w, h, body)


def render(doc, path, opaque):
    with tempfile.NamedTemporaryFile("w", suffix=".svg", delete=False) as f:
        f.write(doc)
    subprocess.run(["rsvg-convert", "-o", path, f.name], check=True)
    os.unlink(f.name)
    if opaque:  # tvOS rejects alpha in the back layer and top shelf images
        subprocess.run(["magick", path, "-background", SEA_LOW, "-alpha", "remove", "-alpha", "off", path],
                       check=True)


def write(path, obj):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as f:
        json.dump(obj, f, indent=2)


def imagestack(name, w, h, scales):
    stack = os.path.join(BRAND, f"{name}.imagestack")
    layers = [("Front", front, False), ("Middle", middle, False), ("Back", back, True)]
    write(os.path.join(stack, "Contents.json"),
          {"info": INFO, "layers": [{"filename": f"{l}.imagestacklayer"} for l, _, _ in layers]})
    for layer, draw, opaque in layers:
        d = os.path.join(stack, f"{layer}.imagestacklayer")
        write(os.path.join(d, "Contents.json"), {"info": INFO})
        images = []
        for sc in scales:
            fn = f"{layer.lower()}@{sc}x.png"
            os.makedirs(os.path.join(d, "Content.imageset"), exist_ok=True)
            render(draw(w * sc, h * sc), os.path.join(d, "Content.imageset", fn), opaque)
            images.append({"filename": fn, "idiom": "tv", "scale": f"{sc}x"})
        write(os.path.join(d, "Content.imageset", "Contents.json"), {"images": images, "info": INFO})


def imageset(name, w, h):
    d = os.path.join(BRAND, f"{name}.imageset")
    images = []
    for sc in (1, 2):
        fn = f"shelf@{sc}x.png"
        os.makedirs(d, exist_ok=True)
        render(shelf(w * sc, h * sc), os.path.join(d, fn), True)
        images.append({"filename": fn, "idiom": "tv", "scale": f"{sc}x"})
    write(os.path.join(d, "Contents.json"), {"images": images, "info": INFO})


if __name__ == "__main__":
    shutil.rmtree(XC, ignore_errors=True)
    write(os.path.join(XC, "Contents.json"), {"info": INFO})
    imagestack("App Icon", 400, 240, (1, 2))
    imagestack("App Icon - App Store", 1280, 768, (1,))
    imageset("Top Shelf Image", 1920, 720)
    imageset("Top Shelf Image Wide", 2320, 720)
    write(os.path.join(BRAND, "Contents.json"), {"info": INFO, "assets": [
        {"filename": "App Icon - App Store.imagestack", "idiom": "tv", "role": "primary-app-icon", "size": "1280x768"},
        {"filename": "App Icon.imagestack", "idiom": "tv", "role": "primary-app-icon", "size": "400x240"},
        {"filename": "Top Shelf Image Wide.imageset", "idiom": "tv", "role": "top-shelf-image-wide", "size": "2320x720"},
        {"filename": "Top Shelf Image.imageset", "idiom": "tv", "role": "top-shelf-image", "size": "1920x720"},
    ]})
    # Flattened previews, for looking at.
    st = os.path.join(BRAND, "App Icon.imagestack")
    subprocess.run(["magick"] + [os.path.join(st, f"{l}.imagestacklayer", "Content.imageset", f"{l.lower()}@2x.png")
                                 for l in ("Back", "Middle", "Front")] + ["-flatten", os.path.join(HERE, "preview.png")],
                   check=True)
    shutil.copy(os.path.join(BRAND, "Top Shelf Image.imageset", "shelf@1x.png"), os.path.join(HERE, "shelf.png"))
    print("wrote", XC, "and previews in", HERE)
