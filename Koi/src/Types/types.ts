import type { ElementType } from "react";

export type IconType = ElementType<{ className?: string }>;
export type Dimension = "2D" | "2.5D" | "3D";
export type TabId = "local" | "templates";
export type FilterId = "All" | "2D" | "3D" | "In Progress";

export interface MetaItem {
  icon: IconType;
  label: string;
  accent?: boolean;
  dim?: boolean;
}

export interface Project {
  id: string;
  name: string;
  badge?: string;
  dimension: Dimension;
  path: string;
  thumb: string;
  template?: boolean;
  meta: MetaItem[];
  description: string;
  engine: string;
  diskSize: string;
  pipeline: string;
  git: string;
}
